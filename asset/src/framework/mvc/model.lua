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

	function MyModel:ctor(id)
		self.super.ctor(self, id)

		self:_defineScheme({
			age = "number",
			name = "string",
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
	assert(type(id) ~= "string", "Invalid model id, id must be string type.")
	self._id = id
	self._scheme = {
		id = "string",
	}
end

function ModelBase:getId()
	return self._id
end

function ModelBase:_defineScheme(scheme)
	if type(scheme) ~= "table" then
		scheme = {}
	end
	for propName, propType in pairs(scheme) do
		if type(propType) == "string" then
			self._scheme[propName] = propType
		end
	end
end

function ModelBase:_setProperties(props)
	if type(props) ~= "table" then
		return
	end
	for propName, propValue in pairs(props) do
		local propType = self._scheme[propName]
		if propType and GetType(propValue) == propType then
			self["_" .. propName] = propValue
		elseif propType == nil then
			log("The property %s doesn't exist in your model scheme.", propName)
		else
			log("Wrong type of the property %s. The value type is %s, but it should be %s.", propName, GetType(propValue), propType)
		end
	end
end

return ModelBase