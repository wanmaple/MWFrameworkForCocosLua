--[[
	Description: to create a lua class
	Author: M.Wan
	Date: 04/13/2014
]]

function luaclass(className, super)
	assert(type(className) == "string" and (type(super) == "table" or type(super) == "nil"), "Invalid params.")

	local cls = {}
	cls.__index = cls

	cls.__className = className

	if super and super.__ctype == 2 then
		cls.__super = super
		-- super class
		setmetatable(cls, super)
	else
		-- indice this class is a lua class
		cls.__ctype = 2

		-- to create object.
		function cls:new()
			local instance = self:__ctor()
			return instance
		end

		-- real constructor, don't call this outside.
		function cls:__ctor()
			local instance = nil
			if self.__super then
				instance = self.__super:__ctor()
			else
				instance = {}
			end

			-- set template pointer
			setmetatable(instance, self)

			return instance
		end

		-- get class name.
		function cls:getType()
			return self.__className
		end
	end

	_G[className] = cls
end