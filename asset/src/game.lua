-- cc.FileUtils:getInstance():addSearchPath("src")
-- cc.FileUtils:getInstance():addSearchPath("res")

require "mwframework"

-- for CCLuaEngine traceback
local function __G__TRACKBACK__(msg)
    log("----------------------------------------")
    log("LUA ERROR: " .. tostring(msg) .. "\n")
    log(debug.traceback())
    log("----------------------------------------")
    return msg
end

local Game = {}

function Game:start()
    local status, msg = xpcall(function() Game:_start() end, __G__TRACKBACK__)
    if not status then
        error(msg)
    end
end

function Game:_init()
    collectgarbage("collect")
    -- avoid memory leak
    collectgarbage("setpause", 100)
    collectgarbage("setstepmul", 5000)
    
    -- initialize director
    local director = cc.Director:getInstance()
    local glview = director:getOpenGLView()
    if glview == nil then
        glview = cc.GLViewImpl:createWithRect("My Game", cc.rect(0, 0, 1136, 640))
        director:setOpenGLView(glview)
    end

    glview:setDesignResolutionSize(1136, 640, cc.ResolutionPolicy.NO_BORDER)

    --turn on display FPS
    director:setDisplayStats(true)

    --set FPS. the default value is 1.0/60 if you don't call this
    director:setAnimationInterval(1.0 / 60)
end

function Game:_run()
    local TestScene = require "src.scenes.TestScene"
    ReplaceScene(TestScene, { STRING = "abc", NUMBER = 123, BOOLEAN = true, REF = mw.ArrayList:create() })
end

function Game:_start()
    Game:_init()
    Game:_run()
end

return Game