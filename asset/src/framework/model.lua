--[[
	Description: Model base
	Author: M.Wan
	Date: 04/29/2014
]]

-- null in database transfered to game is a null string, so when you use a model, you should use DBNULL instead of nil
DBNULL = "null"

luaclass("ModelBase")

-- update indice, instance would call updateFromDB() when indexed if this attribute is true, and the attribute 
-- would be set to false after that.
ModelBase.updateFlag = false
-- update times
ModelBase.updateTimes = 0

-- overwrite constructor
function ModelBase:new()
	local instance = self:__ctor()
	log("Model new [" .. self:getType() .. "]")
	return instance:__createProxy()
end

function ModelBase:updateWithData(data)
	table.deepCopy(self, data)
end

function ModelBase:updateFromDB()
	assert(false, "override me")
end

-- create a proxy for the object, to realize two features:
-- 1. check updateFlag when index an attribute, invoke updateFromDB when it's true.
-- 2. Forbid adding new attributes to the real model instance.
function ModelBase:__createProxy()
	local instance = self
	local proxy = {}
	-- add a reference to the real object
	proxy.__model = instance
	local mt = {
		__index = function(_, key)
			if type(instance[key]) ~= "function" and instance.updateFlag then
				-- don't modify updateFlag in updateFromDB() method, otherwise it may cause endless loop
				instance.updateFlag = false
				instance:updateFromDB()
				instance.updateTimes = instance.updateTimes + 1
			end
			return instance[key]
		end,
		__newindex = function(_, key, value)
			instance[key] = value
		end
	}
	setmetatable(proxy, mt)

	-- remember that the proxy here doesn't have any members even if you add some to it, because all index operations
	-- to this proxy object is exactly affecting its real instance.
	return proxy
end