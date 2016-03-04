--[[
	Description: View base
	Author: M.Wan
	Date: 04/29/2014
]]

local ViewBase = class("ViewBase", function()
	return cc.Node:create()
end)

function ViewBase:ctor(model)
	self._model = model

	self:updateView()
end

function ViewBase:getModel()
	return self._model
end

function ViewBase:setModel(model)
	if self._model ~= model then
		self._model = model
		self:updateView()
	end
end

function ViewBase:updateView()
	assert(false, "override me.")
end

return ViewBase