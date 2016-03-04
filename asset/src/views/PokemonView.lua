

local ViewBase = Import("framework.mvc.view")
local PokemonView = class("PokemonView", ViewBase)

function PokemonView:ctor(model)
	PokemonView.super.ctor(self, model)
end

function PokemonView:updateView()
	local zipData = mw.ZipData:createWithExistingFile("res/GIF/pokemon_gif5.rc", "7ujm,lp-")
	zipData:beginUnzip()
	local data = zipData:getCompressedFileData(self._model:getId() .. ".gif")
	zipData:endUnzip()
	self._gif = mw.GifSprite:createWithRawData(data)
	self._gif:setAnchorPoint(cc.p(0, 0))
	self:addChild(self._gif)
	self:setContentSize(self._gif:getContentSize())
end

return PokemonView