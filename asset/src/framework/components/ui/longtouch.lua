--[[
    Description: Long touch component.
    Author: M.Wan
    Date: 09/4/2015
]]

local Component = Import("..component")
local LongTouchComponent = class("LongTouchComponent", Component)

local UPDATE_SCHEDULER_KEY = "longtouch_update_scheduler"
local DEFAULT_PRESS_TIME = 0.5

function LongTouchComponent:ctor()
	LongTouchComponent.super.ctor(self, "LongTouch")

	self._touchTs = DEFAULT_PRESS_TIME
	self._longTouching = false
end

function LongTouchComponent:getPressTime()
	return self._touchTs
end

function LongTouchComponent:setPressTime(ts)
	assert(type(ts) == "number" and ts > 0, "Invalid params of LongTouchComponent:setPressTime")
	self._touchTs = ts
end

--[[
	onClick, onLongTouchBegan, onLongTouchMoved, onLongTouchEnded, onLongTouchCancelled
]]
function LongTouchComponent:setDelegate(delegate)
	self._delegate = delegate
end

function LongTouchComponent:exportMethods()
	self:_exportMethods({
		"getPressTime",
		"setPressTime",
		"setDelegate",
	})
	return self
end

function LongTouchComponent:_onBind(target)
	local listener = cc.EventListenerTouchOneByOne:create()
	listener:setSwallowTouches(true)
	listener:registerScriptHandler(MakeScriptHandler(self, self._onTouchBegan), cc.Handler.EVENT_TOUCH_BEGAN)
	listener:registerScriptHandler(MakeScriptHandler(self, self._onTouchMoved), cc.Handler.EVENT_TOUCH_MOVED)
	listener:registerScriptHandler(MakeScriptHandler(self, self._onTouchEnded), cc.Handler.EVENT_TOUCH_ENDED)
	listener:registerScriptHandler(MakeScriptHandler(self, self._onTouchCancelled), cc.Handler.EVENT_TOUCH_CANCELLED)
	cc.Director:getInstance():getEventDispatcher():addEventListenerWithSceneGraphPriority(listener, target)
	self._listener = listener
end

function LongTouchComponent:_onUnbind()
	if self._listener then
		cc.Director:getInstance():getEventDispatcher():removeEventListener(self._listener)
		self._listener = nil
	end
end

function LongTouchComponent:_onTouchBegan(touch, event)
	self._currentLoc = touch:getLocation()
	local bound = self._target:getBoundingBoxToWorld()
	if cc.rectContainsPoint(bound, self._currentLoc) then
		self._beginTs = os.clock()
		self:_scheduleUpdate()
		return true
	end
	return false
end

function LongTouchComponent:_onTouchMoved(touch, event)
	self._currentLoc = touch:getLocation()
	if not self._longTouching then
		return
	end
	local bound = self._target:getBoundingBoxToWorld()
	if cc.rectContainsPoint(bound, self._currentLoc) then
		if self._delegate and type(self._delegate.onLongTouchMoved) == "function" then
			self._delegate:onLongTouchMoved(self._target, self._currentLoc, os.clock() - self._beginTs)
		end
	else
		self._longTouching = false
		if self._delegate and type(self._delegate.onLongTouchEnded) == "function" then
			self._delegate:onLongTouchEnded(self._target, self._currentLoc, os.clock() - self._beginTs)
		end
	end
end

function LongTouchComponent:_onTouchEnded(touch, event)
	self._currentLoc = touch:getLocation()
	self:_unscheduleUpdate()
	if self._longTouching then
		local bound = self._target:getBoundingBoxToWorld()
		if cc.rectContainsPoint(bound, self._currentLoc) then
			if self._delegate and type(self._delegate.onClick) == "function" then
				self._delegate:onClick(self._target)
			end
		end
	end
	self._longTouching = false
	self._beginTs = nil
	self._currentLoc = nil
end

function LongTouchComponent:_onTouchCancelled(touch, event)
	self._currentLoc = touch:getLocation()
	self:_unscheduleUpdate()
	if self._longTouching then
		if self._delegate and type(self._delegate.onLongTouchCancelled) == "function" then
			self._delegate:onLongTouchCancelled(self._target, self._currentLoc, os.clock() - self._beginTs)
		end
	end
	self._longTouching = false
	self._beginTs = nil
	self._currentLoc = nil
end

function LongTouchComponent:_update(dt)
	local delta = os.clock() - self._beginTs
	if delta >= self._touchTs then
		self._longTouching = true
		self:_unscheduleUpdate()
		if self._delegate and type(self._delegate.onLongTouchBegan) == "function" then
			self._delegate:onLongTouchBegan(self._target, self._currentLoc, delta)
		end
	end
end

function LongTouchComponent:_scheduleUpdate()
	self._scheduleHandle = cc.Director:getInstance():getScheduler():scheduleScriptFunc(MakeScriptHandler(self, self._update), 0, false)
end

function LongTouchComponent:_unscheduleUpdate()
	if self._scheduleHandle then
		cc.Director:getInstance():getScheduler():unscheduleScriptEntry(self._scheduleHandle)
		self._scheduleHandle = nil
	end
end

return LongTouchComponent