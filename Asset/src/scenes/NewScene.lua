
local NewScene = class("NewScene", function(params)
	return mw.GameScene:createWithParams(params)
end)

function NewScene:onEnter()
	print("onEnter")
end

function NewScene:onExit()
	print("onExit")
end

return NewScene