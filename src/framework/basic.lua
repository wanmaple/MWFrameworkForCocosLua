--[[
	Description: Internal objects extensions
	Author: M.Wan
	Date: 04/26/2014
]]

-- mark as deprecated
function Deprecate(className)
	assert(false, "Deprecated class: " .. className)
end

-- return type string of the instance
function GetType(instance)
	if type(instance) == "table" then
		if instance.__className == nil then
			return tolua.type(instance)
		end
		return instance.__className
	elseif type(instance) == "userdata" then
		return tolua.type(instance)
	else
		return type(instance)
	end
end

-- return instance function pointer
function MakeScriptHandler(target, selector, ...)
	local args = {...}
	return function(...)
		-- the varadic params here are sent by the event automatically, append our own args after them.
		local internalArgs = {...}
		for _, arg in ipairs(args) do
			table.insert(internalArgs, arg)
		end
		return selector(target, unpack(internalArgs))
	end
end

-- call a function after delay
function CallFunctionAsync(target, selector, delay, ...)
	local args = {...}
	local handlerId = nil
	local handlerFunction = function()
		selector(target, unpack(args))
		cc.Director:getInstance():getScheduler():unscheduleScriptEntry(handlerId)
	end
	handlerId = cc.Director:getInstance():getScheduler():scheduleScriptFunc(handlerFunction, delay, false)
end

-- switch scene
function ReplaceScene(scene, params)
	if type(scene) == "string" then
		scene = _G[scene]
	end
	local newScene = scene["create"](scene, params)

	local currentScene = cc.Director:getInstance():getRunningScene()
	if currentScene then
		cc.Director:getInstance():replaceScene(newScene)
	else
		cc.Director:getInstance():runWithScene(newScene)
	end
end

-- check whether fall in the random area, such as fallInRandom(3, 7) means whether it falls in 3/7.
function FallInRandom(numerator, denominator)
	local randomNum = math.random(1, denominator)
	return randomNum <= numerator
end

-- check whether a rect contains a point.
function ContainsPoint(rect, pos)
	return pos.x >= rect.x and pos.x <= rect.x + rect.width and pos.y >= rect.y and pos.y <= rect.y + rect.height
end

function PositionEquals(pos1, pos2)
	return pos1.x == pos2.x and pos1.y == pos2.y
end

-- return an array which contains all UTF-8 substrings from a string, from the first character.
function GenerateAllUTF8Substrings(text)
	if type(text) ~= "string" then
		return nil
	end
	local function isChinese(index)
		-- the high 4 bits of UTF-8 Chinese is 1110
		local byte = string.byte(text, index)
		byte = bit:_rshift(byte, 4)
		if byte == 0xE then
			return true
		end
		return false
	end

	local strings = {}
	local index = 1
	while index <= #text do
		if isChinese(index) then
			index = index + 3
		else
			index = index + 1
		end
		local substr = string.sub(text, 1, index - 1)
		table.insert(strings, substr)
	end

	return strings
end

-- create frame animation
function CreateAnimation(frameName, frameCount, timeline, seperator)
	seperator = seperator or ""

	local frames = {}
	for i = 1, frameCount do
		local frame = cc.SpriteFrameCache:getInstance():getSpriteFrame(frameName .. seperator .. tostring(i) .. ".png")
		table.insert(frames, frame)
	end
	table.insert(frames, cc.SpriteFrameCache:getInstance():getSpriteFrame(frameName .. seperator .. 1 .. ".png"))
	local animation = cc.Animation:createWithSpriteFrames(frames, timeline)
	local animate = cc.Animate:create(animation)

	return animate
end

-- add frames to the cache
function LoadSpriteFrames(frames)
	for i = 1, #frames, 2 do
		log(string.format("Load sprite frame: %s", frames[i]))
		cc.SpriteFrameCache:getInstance():addSpriteFrames(frames[i], frames[i + 1])
	end
end

-- remove frames
function RemoveSpriteFrames(frames)	
	for i = 1, #frames, 2 do
		log(string.format("Remove sprite frame: %s", frames[i]))
		cc.SpriteFrameCache:getInstance():removeSpriteFramesFromFile(frames[i])
		cc.SpriteFrameCache:getInstance():removeSpriteFramesFromTexture(frames[i + 1])
	end
end

-- use coroutine to run multiple actions
-- warning: you have to use this function in a coroutine
-- invoke this as CoPerformActions(target1, action1[, target2, action2] ...)
function CoPerformActions(...)
	local co = coroutine.running()
	assert(co, "CoPerformActions should only be used in a coroutine")
	local actions = {...}

	local maxDuration = -1
	local maxDurationTarget = nil

	for i = 1, #actions, 2 do
		local target = actions[i]
		local action = actions[i + 1]
		local duration = action:getDuration()
		-- seek the longest-duration action target
		if duration > maxDuration then
			maxDuration = duration
			maxDurationTarget = target
		end
		target:runAction(action)
	end

	-- wait for the longest action
	local coAction = cc.Sequence:create(
		cc.DelayTime:create(maxDuration),
		cc.CallFunc:create(function() coroutine.resume(co) end)
		)
	maxDurationTarget:runAction(coAction)
	coroutine.yield()
end