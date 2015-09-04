
local Component = Import("..component")
local FiniteStateMachine = class("FiniteStateMachine", Component)

--[[
    port from Javascript State Machine Library
    https://github.com/jakesgordon/javascript-state-machine
]]

-- the event transitioned successfully from one state to another
FiniteStateMachine.SUCCEEDED = 1
-- the event was successfull but no state transition was necessary
FiniteStateMachine.NOTRANSITION = 2
-- the event was cancelled by the caller in a beforeEvent callback
FiniteStateMachine.CANCELLED = 3
-- the event is asynchronous and the caller is in control of when the transition occurs
FiniteStateMachine.PENDING = 4
-- the event was failure
FiniteStateMachine.FAILURE = 5

-- caller tried to fire an event that was innapropriate in the current state
FiniteStateMachine.INVALID_TRANSITION_ERROR = "INVALID_TRANSITION_ERROR"
-- caller tried to fire an event while an async transition was still pending
FiniteStateMachine.PENDING_TRANSITION_ERROR = "PENDING_TRANSITION_ERROR"
-- caller provided callback function threw an exception
FiniteStateMachine.INVALID_CALLBACK_ERROR = "INVALID_CALLBACK_ERROR"

FiniteStateMachine.WILDCARD = "*"
FiniteStateMachine.ASYNC = "ASYNC"

function FiniteStateMachine:ctor()
    FiniteStateMachine.super.ctor(self, "FiniteStateMachine")
end

function FiniteStateMachine:setupState(cfg)
    assert(type(cfg) == "table", "Invalid param cfg.")

    -- cfg.initial allow for a simple string,
    -- or an table with { state = "foo", event = "setup", defer = true|false }
    if type(cfg.initial) == "string" then
        self._initial = {state = cfg.initial}
    else
        self._initial = clone(cfg.initial)
    end

    self._terminal   = cfg.terminal or cfg.final
    self._events     = cfg.events or {}
    self._callbacks  = cfg.callbacks or {}
    self._map        = {}
    self._current    = "none"
    self._inTransition = false

    if self._initial then
        self._initial.event = self._initial.event or "startup"
        self:_addEvent({name = self._initial.event, from = "none", to = self._initial.state})
    end

    for _, event in ipairs(self._events) do
        self:_addEvent(event)
    end

    if self._initial and not self._initial.defer then
        self:doEvent(self._initial.event)
    end

    return self._target
end

function FiniteStateMachine:isReady()
    return self._current ~= "none"
end

function FiniteStateMachine:getState()
    return self._current
end

function FiniteStateMachine:isState(state)
    if type(state) == "table" then
        for _, s in ipairs(state) do
            if s == self._current then return true end
        end
        return false
    else
        return self._current == state
    end
end

function FiniteStateMachine:canDoEvent(eventName)
    return not self._inTransition
        and (self._map[eventName][self._current] ~= nil or self._map[eventName][FiniteStateMachine.WILDCARD] ~= nil)
end

function FiniteStateMachine:cannotDoEvent(eventName)
    return not self:canDoEvent(eventName)
end

function FiniteStateMachine:isFinishedState()
    return self:isState(self._terminal)
end

function FiniteStateMachine:doEventForce(name, ...)
    local from = self._current
    local map = self._map[name]
    local to = (map[from] or map[FiniteStateMachine.WILDCARD]) or from
    local args = {...}

    local event = {
        name = name,
        from = from,
        to = to,
        args = args,
    }

    if self._inTransition then self._inTransition = false end
    self:_beforeEvent(event)
    if from == to then
        self:_afterEvent(event)
        return FiniteStateMachine.NOTRANSITION
    end

    self._current = to
    self:_enterState(event)
    self:_changeState(event)
    self:_afterEvent(event)
    return FiniteStateMachine.SUCCEEDED
end

function FiniteStateMachine:doEvent(name, ...)
    assert(self._map[name] ~= nil, string.format("FiniteStateMachine:doEvent() - invalid event %s", tostring(name)))

    local from = self._current
    local map = self._map[name]
    local to = (map[from] or map[FiniteStateMachine.WILDCARD]) or from
    local args = {...}

    local event = {
        name = name,
        from = from,
        to = to,
        args = args,
    }

    if self._inTransition then
        self:_onError(event,
                      FiniteStateMachine.PENDING_TRANSITION_ERROR,
                      "event " .. name .. " inappropriate because previous transition did not complete")
        return FiniteStateMachine.FAILURE
    end

    if self:cannotDoEvent(name) then
        self:_onError(event,
                      FiniteStateMachine.INVALID_TRANSITION_ERROR,
                      "event " .. name .. " inappropriate in current state " .. self._current)
        return FiniteStateMachine.FAILURE
    end

    if self:_beforeEvent(event) == false then
        return FiniteStateMachine.CANCELLED
    end

    if from == to then
        self:_afterEvent(event)
        return FiniteStateMachine.NOTRANSITION
    end

    event.transition = function()
        self._inTransition  = false
        self._current = to -- this method should only ever be called once
        self:_enterState(event)
        self:_changeState(event)
        self:_afterEvent(event)
        return FiniteStateMachine.SUCCEEDED
    end

    event.cancel = function()
        -- provide a way for caller to cancel async transition if desired
        event.transition = nil
        self:_afterEvent(event)
    end

    self._inTransition = true
    local leave = self:_leaveState(event)
    if leave == false then
        event.transition = nil
        event.cancel = nil
        self._inTransition = false
        return FiniteStateMachine.CANCELLED
    elseif string.upper(tostring(leave)) == FiniteStateMachine.ASYNC then
        return FiniteStateMachine.PENDING
    else
        -- need to check in case user manually called transition()
        -- but forgot to return FiniteStateMachine.ASYNC
        if event.transition then
            return event.transition()
        else
            self._inTransition = false
        end
    end
end

function FiniteStateMachine:exportMethods()
    self:_exportMethods({
        "setupState",
        "isReady",
        "getState",
        "isState",
        "canDoEvent",
        "cannotDoEvent",
        "isFinishedState",
        "doEventForce",
        "doEvent",
    })
    return self
end

function FiniteStateMachine:_onBind()
end

function FiniteStateMachine:_onUnbind()
end

function FiniteStateMachine:_addEvent(event)
    local from = {}
    if type(event.from) == "table" then
        for _, name in ipairs(event.from) do
            from[name] = true
        end
    elseif event.from then
        from[event.from] = true
    else
        -- allow "wildcard" transition if "from" is not specified
        from[FiniteStateMachine.WILDCARD] = true
    end

    self._map[event.name] = self._map[event.name] or {}
    local map = self._map[event.name]
    for fromName, _ in pairs(from) do
        map[fromName] = event.to or fromName
    end
end

local function _doCallback(callback, event)
    if callback then return callback(event) end
end

function FiniteStateMachine:_beforeAnyEvent(event)
    return _doCallback(self._callbacks["onbeforeevent"], event)
end

function FiniteStateMachine:_afterAnyEvent(event)
    return _doCallback(self._callbacks["onafterevent"] or self._callbacks["onevent"], event)
end

function FiniteStateMachine:_leaveAnyState(event)
    return _doCallback(self._callbacks["onleavestate"], event)
end

function FiniteStateMachine:_enterAnyState(event)
    return _doCallback(self._callbacks["onenterstate"] or self._callbacks["onstate"], event)
end

function FiniteStateMachine:_changeState(event)
    return _doCallback(self._callbacks["onchangestate"], event)
end

function FiniteStateMachine:_beforeThisEvent(event)
    return _doCallback(self._callbacks["onbefore" .. event.name], event)
end

function FiniteStateMachine:_afterThisEvent(event)
    return _doCallback(self._callbacks["onafter" .. event.name] or self._callbacks["on" .. event.name], event)
end

function FiniteStateMachine:_leaveThisState(event)
    return _doCallback(self._callbacks["onleave" .. event.from], event)
end

function FiniteStateMachine:_enterThisState(event)
    return _doCallback(self._callbacks["onenter" .. event.to] or self._callbacks["on" .. event.to], event)
end

function FiniteStateMachine:_beforeEvent(event)
    if self:_beforeThisEvent(event) == false or self:_beforeAnyEvent(event) == false then
        return false
    end
end

function FiniteStateMachine:_afterEvent(event)
    self:_afterThisEvent(event)
    self:_afterAnyEvent(event)
end

function FiniteStateMachine:_leaveState(event, transition)
    local specific = self:_leaveThisState(event, transition)
    local general = self:_leaveAnyState(event, transition)
    if specific == false or general == false then
        return false
    elseif string.upper(tostring(specific)) == FiniteStateMachine.ASYNC
        or string.upper(tostring(general)) == FiniteStateMachine.ASYNC then
        return FiniteStateMachine.ASYNC
    end
end

function FiniteStateMachine:_enterState(event)
    self:_enterThisState(event)
    self:_enterAnyState(event)
end

function FiniteStateMachine:_onError(event, error, message)
    log("%s [FiniteStateMachine] ERROR: error %s, event %s, from %s to %s", tostring(self._target), tostring(error), event.name, event.from, event.to)
    logError(message)
end

return FiniteStateMachine
