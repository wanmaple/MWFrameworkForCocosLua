

local Pokemon = Import(".Pokemon")
local SpecialPokemon = class("SpecialPokemon", Pokemon)

function SpecialPokemon:ctor(id)
	SpecialPokemon.super.ctor(self, id)

	self:_defineScheme({
		weight = { "number", 0 },
		height = { "number", 0 },
		})
	self:_setProperties({
		weight = tonumber(mw.SqliteDb:openDb("icon.jpg"):executeQuery("select [weight] from [pet_info] where id = '" .. self._id .. "'")[1].weight),
		height = tonumber(mw.SqliteDb:openDb("icon.jpg"):executeQuery("select [height] from [pet_info] where id = '" .. self._id .. "'")[1].height),
		})
end

function SpecialPokemon:getWeight()
	return self._weight
end

function SpecialPokemon:getHeight()
	return self._height
end

return SpecialPokemon