--[[
	Description: To create class
	Author: M.Wan
	Date: 04/15/2014
]]

local CLASS_TYPE = {
	INHERIT_FROM_CPP = 1,
	INHERIT_FROM_LUA = 2,
}

function class(className, super)
	assert(type(className) == "string" and #className > 0, "Invalid class name.")
	local stype = type(super)
	assert(stype == "table" or stype == "function" or stype == "nil", "Invalid super class.")

	local cls = {}
	cls.__index = cls
	cls.__cname = className

	if stype == "table" and super.__ctype == CLASS_TYPE.INHERIT_FROM_CPP then
		-- cpp super class
		setmetatable(cls, super)
		cls.super = super
	elseif stype == "function" then
		-- the first time to define class inherits cpp class
		function cls.__create(...)
			return super(...)
		end

		cls.__ctype = CLASS_TYPE.INHERIT_FROM_CPP

		function cls:ctor() 
			-- constructor
		end

		function cls.new(...)
			local instance = cls.__create(...)
			local peer = {}
			setmetatable(peer, cls)
			tolua.setpeer(instance, peer)
			instance.class = cls
			instance:ctor(...)
			return instance
		end
	elseif stype == "nil" then
		-- the first time to define lua class
		cls.__ctype = CLASS_TYPE.INHERIT_FROM_LUA

		function cls:ctor()
			-- constructor
		end

		function cls.new(...)
			local instance = {}
			setmetatable(instance, cls)
			instance.class = cls
			instance:ctor(...)
			return instance
		end
	elseif stype == "table" and super.__ctype == CLASS_TYPE.INHERIT_FROM_LUA then
		-- lua super class
		setmetatable(cls, super)
		cls.super = super

		function cls.new(...)
			local instance = {}
			setmetatable(instance, cls)
			instance.class = cls
			instance:ctor(...)
			return instance
		end
	end

	return cls
end