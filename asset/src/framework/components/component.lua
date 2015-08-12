--[[
    Description: Component base
    Author: M.Wan
    Date: 08/12/2015
]]

local Component = class("Component")

function Component:ctor(name, depends)
    self._name = name
    self._depends = depends or {}
end

function Component:getName()
    return self._name
end

function Component:getDepends()
    return self._depends
end

function Component:getTarget()
    return self._target
end

function Component:_exportMethods(methods)
    self._exportedMethods = methods
    local target = self._target
    local com = self
    for _, key in ipairs(methods) do
        if not target[key] then
            local m = com[key]
            target[key] = function(_, ...)
                return m(com, ...)
            end
        end
    end
    return self
end

function Component:_bind(target)
    self._target = target
    for _, name in ipairs(self._depends) do
        if not target:checkComponent(name) then
            target:addComponent(name)
        end
    end
    self:_onBind(target)
end

function Component:_unbind()
    if self._exportedMethods then
        local target = self._target
        for _, key in ipairs(self._exportedMethods) do
            target[key] = nil
        end
    end
    self:_onUnbind()
end

function Component:_onBind()
end

function Component:_onUnbind()
end

return Component
