--[[
	Description: Model base
	Author: M.Wan
	Date: 04/29/2014
]]

local ModelBase = class("ModelBase")

--[[
	When you define your model, you must not forget to use _defineScheme method to define your model properties unless you know 
	what you are doing.
	Scheme indicates the basic properties of the model. And when you set the scheme property of the model, you should use 
	"self:_setProperties({prop = value})" instead of "self._prop = value".

	e.g.
	local MyModel = class("MyModel", ModelBase)

	function MyModel:ctor(id, name, age)
		self.super.ctor(self, id)

		self:_defineScheme({
			age = { function(val) {
				return type(val) == "number" and val >= 0
			}, 0 },
			name = { "string", nil },
		})
		self:_setProperties({
			name = name,
			age = age,
		})
	end

	function MyModel:getAge()
		return self._age
	end

	function MyModel:getName()
		return self._name
	end

	function MyModel:grow()
		self:_setProperties({ age = self._age + 1 })
	end

	function MyModel:changeName(newName)
		self:_setProperties({ name = newName })
	end
]]
function ModelBase:ctor(id)
	assert(type(id) == "string", "Invalid model id, id must be string type.")
	self._scheme = {
		id = "string",
	}
	self._id = id
end

function ModelBase:getId()
	return self._id
end

function ModelBase:_defineScheme(scheme)
	if self._inited then
		return
	end
	if type(scheme) ~= "table" then
		scheme = {}
	end
	self._scheme = { id = "string" }
	for propName, propAttr in pairs(scheme) do
		local propType = propAttr[1]
		local propDef = propAttr[2]
		if type(propType) == "string" or type(propType) == "function" then
			self._scheme[propName] = propType
			self["_" .. propName] = propDef
		end
	end
	self._inited = true
end

function ModelBase:_setProperties(props)
	if type(props) ~= "table" then
		return
	end
	for propName, propValue in pairs(props) do
		local propAttr = self._scheme[propName]
		local propType = propAttr
		if propType == nil then
			log("The property %s doesn't exist in your model scheme.", propName)
		elseif (type(propType) == "string" and GetType(propValue) == propType)
			or (type(propType) == "function" and propType(propValue)) then
			self["_" .. propName] = propValue
		else
			log("Invalid property value of %s.", propName)
		end
	end
end

return ModelBase