class("TestScene", clsGameScene)

require "scenes.TestViewController"

function TestScene:onEnter()
	local testVc = TestViewController:create()
	self:loadViewController(testVc, "TEST_VIEW_CONTROLLER")
end

function TestScene:onExit()

end