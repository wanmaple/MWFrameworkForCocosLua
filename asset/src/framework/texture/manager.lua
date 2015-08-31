--[[
	Description: Ref count machanism to manage textures.
	Author: M.Wan
	Date: 09/1/2015
]]

--[[
 * TextureManager is used to manage textures life cycle based on reference count machanism.
 * The reference count will increase 1 every time you load a texture, vice versa.
 * @func loadTexture: load a texture. (sync)
 * @func unloadTexture: unload a texture.
 * @func didLoadTexture: whether did load the texture.
 * @func loadTextureAsync: load a texture. (async)
 * @func forceUnloadTexture: force unload a texture, which will ignore the reference count.
 * @func setPvrTexturesSupportPremultipliedAlpha: set if .pvr texture supports premultiplied alpha.
 ]]
local TextureManager = {}

TextureManager._textureMap = {}

function TextureManager:loadTexture(plist, texture)
	if type(plist) ~= "string" then
		logError("Invalid param 'plist', should be a string value.")
		return
	end
	if type(texture) ~= "string" then
		logError("Invalid param 'texture', should be a string value.")
		return
	end
	if self._textureMap[plist] then
		self._textureMap[plist]["ref"] = self._textureMap[plist]["ref"] + 1
	else
		cc.SpriteFrameCache:getInstance():addSpriteFrames(plist, texture)
		self._textureMap[plist] = {
			ref = 1,
			tex = texture,
		}
	end
	log("Texture %s loaded, reference count: %d", plist, self._textureMap[plist]["ref"])
end

function TextureManager:unloadTexture(plist)
	if type(plist) ~= "string" then
		logError("Invalid param 'plist', should be a string value.")
		return
	end
	if not self:didLoadTexture(plist) then
		logError("The texture %s hasn't been loaded.", plist)
		return
	end
	log("Texture %s unloaded, reference count: %d", plist, self._textureMap[plist]["ref"])
	if self._textureMap[plist]["ref"] <= 0 then
		cc.SpriteFrameCache:getInstance():removeSpriteFramesFromFile(plist)
		cc.Director:getTextureCache():removeTextureForKey(self._textureMap[plist]["tex"])
		self._textureMap[plist] = nil
	end
end

function TextureManager:didLoadTexture(plist)
	return self._textureMap[plist] ~= nil
end

function TextureManager:loadTextureAsync(plist, texture, callback)
	if type(plist) ~= "string" then
		logError("Invalid param 'plist', should be a string value.")
		return
	end
	if type(texture) ~= "string" then
		logError("Invalid param 'texture', should be a string value.")
		return
	end
	if type(callback) ~= "function" then
		logError("Invalid param 'callback', should be a function.")
		return
	end
	if self:didLoadTexture(plist) then
		self._textureMap[plist]["ref"] = self._textureMap[plist]["ref"] + 1
		callback()
	else
		local realCallback = function()
			cc.SpriteFrameCache:getInstance():addSpriteFrames(plist, texture)
			self._textureMap[plist] = {
				ref = 1,
				tex = texture,
			}
			log("Texture %s loaded, reference count: %d", plist, self._textureMap[plist]["ref"])
			callback()
		end
		cc.Director:getTextureCache():addImageAsync(texture, realCallback)
	end
end

function TextureManager:forceUnloadTexture(plist)
	if type(plist) ~= "string" then
		logError("Invalid param 'plist', should be a string value.")
		return
	end
	if not self:didLoadTexture(plist) then
		logError("The texture %s hasn't been loaded.", plist)
		return
	end
	cc.SpriteFrameCache:getInstance():removeSpriteFramesFromFile(plist)
	cc.Director:getTextureCache():removeTextureForKey(self._textureMap[plist]["tex"])
	self._textureMap[plist] = nil
end

function TextureManager:setPvrTexturesSupportPremultipliedAlpha(bSupport)
	cc.Image:setPVRImagesHavePremultipliedAlpha(bSupport);
end

return TextureManager