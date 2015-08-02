--[[
	Description: Internal objects extensions
	Author: M.Wan
	Date: 04/26/2014
]]

-- return type string of the instance
function GetType(instance)
	if type(instance) == "table" then
		if instance.__cname == nil then
			return tolua.type(instance)
		end
		return instance.__cname
	elseif type(instance) == "userdata" then
		return tolua.type(instance)
	end
	return type(instance)
end

-- simpler method to require module, if you didn't use this method in the global scope, please assign currentModuleName manually.
function Import(moduleName, currentModuleName)
    local currentModuleNameParts = nil
    local moduleFullName = moduleName
    local offset = 1

    while true do
        if string.byte(moduleName, offset) ~= 46 then -- .
            moduleFullName = string.sub(moduleName, offset)
            if currentModuleNameParts and #currentModuleNameParts > 0 then
                moduleFullName = table.concat(currentModuleNameParts, ".") .. "." .. moduleFullName
            end
            break
        end
        offset = offset + 1

        if not currentModuleNameParts then
            if not currentModuleName then
                local n, v = debug.getlocal(3, 1)
                currentModuleName = v
            end

            currentModuleNameParts = string.split(currentModuleName, ".")
            table.dump(currentModuleNameParts)
        end
        table.remove(currentModuleNameParts, #currentModuleNameParts)
    end

    return require(moduleFullName)
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
	return handlerId
end

-- switch scene
function ReplaceScene(scene, params)
	local newScene = scene.new(params)

	local currentScene = cc.Director:getInstance():getRunningScene()
	if currentScene then
		cc.Director:getInstance():replaceScene(newScene)
	else
		cc.Director:getInstance():runWithScene(newScene)
	end
end