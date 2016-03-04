

local ModelBase = Import("framework.mvc.model")
local Pokemon = class("Pokemon", ModelBase)

function Pokemon:ctor(id)
	Pokemon.super.ctor(self, id)

	self:_defineScheme({
		name = { "string", "" }
		})
	self:_setProperties({
		name = mw.SqliteDb:openDb("icon.jpg"):executeQuery("select [name] from [pet_info] where id = '" .. self._id .. "'")[1].name
		})
end

function Pokemon:getName()
	return self._name
end

return Pokemon