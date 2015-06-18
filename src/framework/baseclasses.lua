--[[
	Description: Cpp class extends.
	Author: M.Wan
	Date: 04/26/2014
]]

class("clsNode", {
		create = function()
			return cc.Node:create()
		end
	})

class("clsSprite", {
		create = function(...)
			return cc.Sprite:create(...)
		end,
		createWithTexture = function(...)
			return cc.Sprite:createWithTexture(...)
		end,
		createWithSpriteFrame = function(...)
			return cc.Sprite:createWithSpriteFrame(...)
		end,
		createWithSpriteFrameName = function(...)
			return cc.Sprite:createWithSpriteFrameName(...)
		end
	})

class("clsLayer", {
		create = function()
			return cc.Layer:create()
		end
	})

class("clsLayerColor", {
		create = function(...)
			return cc.LayerColor:create(...)
		end
	})

class("clsGameScene", {
		create = function(...)
			local args = {...}
			if #args > 0 then
				return mw.GameScene:createWithParams(args)
			else
				return mw.GameScene:create()
			end
		end
	})

class("clsViewController", {
		create = function()
			return mw.ViewController:create()
		end
	})

class("clsViewSegue", {
		create = function()
			return mw.ViewSegue:create()
		end
	})