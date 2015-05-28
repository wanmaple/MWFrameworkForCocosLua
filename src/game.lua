cc.FileUtils:getInstance():addSearchPath("src")
cc.FileUtils:getInstance():addSearchPath("res")

require "cocos.init"

-- for CCLuaEngine traceback
local function __G__TRACKBACK__(msg)
    cclog("----------------------------------------")
    cclog("LUA ERROR: " .. tostring(msg) .. "\n")
    cclog(debug.traceback())
    cclog("----------------------------------------")
    return msg
end

local Game = {}

local winSize = cc.Director:getInstance():getWinSize()

function Game:init()
    collectgarbage("collect")
    -- avoid memory leak
    collectgarbage("setpause", 100)
    collectgarbage("setstepmul", 5000)
    
    -- initialize director
    local director = cc.Director:getInstance()
    local glview = director:getOpenGLView()
    if nil == glview then
        glview = cc.GLViewImpl:createWithRect("TestFramework", cc.rect(0, 0, 900, 640))
        director:setOpenGLView(glview)
    end

    glview:setDesignResolutionSize(960, 640, cc.ResolutionPolicy.NO_BORDER)

    --turn on display FPS
    director:setDisplayStats(true)

    --set FPS. the default value is 1.0/60 if you don't call this
    director:setAnimationInterval(1.0 / 60)
end

function Game:run()
    local scene = mw.GameScene:create()
    local layer = cc.Layer:create()
    scene:addChild(layer)

    local pZip = mw.ZipData:createWithExistingFile("res/493.zip")
    pZip:beginUnzip()
    local pGif = mw.GifSprite:createWithRawData(pZip:getCompressedFileData("493.gif"))
    pZip:endUnzip()
    pGif:setPosition(winSize.width * 0.5, winSize.height * 0.5)
    pGif:setScale(2)
    pGif:setSpeedRatio(1.5)
    layer:addChild(pGif)

    cc.Director:getInstance():runWithScene(scene)
end

function Game:start()
	local status, msg = xpcall(function() Game:__start() end, __G__TRACKBACK__)
	if not status then
	    error(msg)
	end
end

function Game:__start()
    Game:init()
    Game:run()
end

return Game