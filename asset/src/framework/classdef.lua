--[[
	Description: To create class
	Author: M.Wan
	Date: 04/15/2014
]]

local CLASS_TYPE = {
	INHERIT_FROM_CPP = 1,
	INHERIT_FROM_LUA = 2,
}

local function setmetatableindex(t, index)
	if type(t) == "userdata" then
		local peer = tolua.getpeer(t)
		if not peer then
			peer = {}
			tolua.setpeer(t, peer)
		end
		setmetatableindex(peer, index)
	else
		local mt = getmetatable(t)
		if not mt then
			mt = {}
		end
		if not mt.__index then
			mt.__index = index
			setmetatable(t, mt)
		elseif mt.__index ~= index then
			setmetatableindex(mt, index)
		end
	end
end

function class(className, super)
	assert(type(className) == "string" and #className > 0, "Invalid class name.")
	local stype = type(super)
	assert(stype == "table" or stype == "function" or stype == "nil", "Invalid super class.")

	local cls = {}
	cls.__index = cls
	cls.__cname = className

	if stype == "table" and super.__ctype == CLASS_TYPE.INHERIT_FROM_CPP then
		-- cpp super class
		setmetatable(cls, { __index = super })
		cls.super = super
	elseif stype == "function" then
		-- the first time to define class inherits cpp class
		function cls.__create(...)
			return super(...)
		end

		cls.__ctype = CLASS_TYPE.INHERIT_FROM_CPP
	elseif stype == "nil" then
		-- the first time to define lua class
		cls.__ctype = CLASS_TYPE.INHERIT_FROM_LUA
	elseif stype == "table" and super.__ctype == CLASS_TYPE.INHERIT_FROM_LUA then
		-- lua super class
		setmetatable(cls, { __index = super })
		cls.super = super
	end

	if not cls.ctor then
		function cls:ctor(...)
		end
	end

	function cls.new(...)
		local instance
		if cls.__create then
			instance = cls.__create(...)
		else
			instance = {}
		end
		setmetatableindex(instance, cls)
		instance.class = cls
		instance:ctor(...)
		return instance
	end

	return cls
end