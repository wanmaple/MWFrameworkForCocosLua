--[[
	Description: Save device information
	Author: M.Wan
	Date: 06/18/2015
]]

Device = {}

local app = cc.Application:getInstance()

--[[
cc.PLATFORM_OS_WINDOWS = 0
cc.PLATFORM_OS_LINUX   = 1
cc.PLATFORM_OS_MAC     = 2
cc.PLATFORM_OS_ANDROID = 3
cc.PLATFORM_OS_IPHONE  = 4
cc.PLATFORM_OS_IPAD    = 5
cc.PLATFORM_OS_BLACKBERRY = 6
cc.PLATFORM_OS_NACL    = 7
cc.PLATFORM_OS_EMSCRIPTEN = 8
cc.PLATFORM_OS_TIZEN   = 9
cc.PLATFORM_OS_WINRT   = 10
cc.PLATFORM_OS_WP8     = 11
]]
function Device:getPlatform()
	return app:getTargetPlatform()
end

--[[
cc.LANGUAGE_ENGLISH    = 0
cc.LANGUAGE_CHINESE    = 1
cc.LANGUAGE_FRENCH     = 2
cc.LANGUAGE_ITALIAN    = 3
cc.LANGUAGE_GERMAN     = 4
cc.LANGUAGE_SPANISH    = 5
cc.LANGUAGE_RUSSIAN    = 6
cc.LANGUAGE_KOREAN     = 7
cc.LANGUAGE_JAPANESE   = 8
cc.LANGUAGE_HUNGARIAN  = 9
cc.LANGUAGE_PORTUGUESE = 10
cc.LANGUAGE_ARABIC     = 11
]]
function Device:getLanguage()
	return app:getCurrentLanguage()
end

function Device:getWinSize()
	return cc.Director:getInstance():getWinSize()
end