
local TestScene = class("TestScene", function(params)
	return mw.GameScene:createWithParams(params)
end)

local TestViewController = Import("..controllers.TestViewController")

function TestScene:onEnter()
	local testVc = TestViewController.new()
	self:loadViewController(testVc, "TEST_VIEW_CONTROLLER")
end

function TestScene:onExit()

end

return TestScene