
local TestViewController = class("TestViewController", function()
	return mw.ViewController:create()
end)

local Pokemon = Import("..models.Pokemon")
local PokemonView = Import("..views.PokemonView")

function TestViewController:viewDidLoad()
	log("Test GameScene parameters...")
	log("NUMBER: %d", self:scene():getNumberParameter("NUMBER"))
	log("STRING: %s", self:scene():getStringParameter("STRING"))
	log("BOOLEAN: %s", tostring(self:scene():getBooleanParameter("BOOLEAN")))
	log("REF: %s", GetType(self:scene():getRefParameter("REF")))

	log("Test ZipData and GifSprite...")
	local pokemon1 = Pokemon.new("492")
	print("POKEMON1 NAME: " .. pokemon1:getName())
	local pokemon2 = Pokemon.new("493")
	print("POKEMON2 NAME: " .. pokemon2:getName())
	local view1 = PokemonView.new(pokemon1)
	local view2 = PokemonView.new(pokemon2)

	local pDict = mw.Dictionary:create()
	pDict:setObjectForKey("GIF1", view1)
	pDict:setObjectForKey("GIF2", view2)

	local keys = pDict:allKeys()
	for i, key in ipairs(keys) do
		local view = pDict:objectForKey(key)
		view:setPosition(Device:width() * (0.25 + (i - 1) * 0.5), Device:height() * 0.5)
		self:view():addChild(view)
	end

    local svg = mw.SvgSprite:createWithFile("tiger.svg")
    svg:setPosition(Device:cx(), Device:cy())
    svg:setVectorScale(0.5)
    self:view():addChild(svg)

	bindable(svg):addComponent("framework.components.ui.longtouch"):exportMethods()
		:setDelegate(self)
	bindable(view1):addComponent("framework.components.ui.longtouch"):exportMethods()
		:setDelegate(self)
	bindable(view2):addComponent("framework.components.ui.longtouch"):exportMethods()
		:setDelegate(self)
	view1:setPressTime(0.05)
	view2:setPressTime(0.05)

	log("Test Sqlite DB...")
	local db = mw.SqliteDb:openDb("icon.jpg")
	local t = db:executeQuery("select * from [pet_info] where [id] = '493'");
	table.dump(t)

	log("Test some utils...")
	local reachabilityStrMap = {
		[0] = "No network.",
		[1] = "Wifi",
		[2] = "WWAN",
	}
	log("NetStatus: %s", reachabilityStrMap[mw.SystemHelper:getInstance():checkNetStatus()])
	log("UUID: %s", mw.UUIDGenerator:getInstance():generateUUID())

	log("Test protobuf...")
	local pb = protobuf
	pb.register_file(cc.FileUtils:getInstance():fullPathForFilename("res/addressbook.pb"))
	local code = pb.encode("tutorial.Person", {
			name = "Winder",
			id = 18,
			phone = {
				{ number = "021-55555555" },
				{ number = "13311122244", type = "WORK" }
			}
		})
	log("DECODING...")
	local data = pb.decode("tutorial.Person", code)
	log("ID: %d", data.id)
	log("NAME: %s", data.name)
	log("PHONE: ")
	for _, v in ipairs(data.phone) do
		log("\t%s\t%s", v.number, v.type)
	end
end

function TestViewController:viewDidUnload()

end

function TestViewController:onLongTouchBegan(target, loc, ts)
	print("TestViewController:onLongTouchBegan", target, loc, ts)
	self._beginPos = target:convertToNodeSpace(loc)
end

function TestViewController:onLongTouchMoved(target, loc, ts)
	print("TestViewController:onLongTouchMoved", target, loc, ts)
	local vec = cc.pSub(target:convertToNodeSpace(loc), self._beginPos)
	target:setPosition(cc.pAdd(cc.p(target:getPosition()), vec))
end

function TestViewController:onLongTouchEnded(target, loc, ts)
	print("TestViewController:onLongTouchEnded", target, loc, ts)
	self._beginPos = nil
end

function TestViewController:onClick(target)
	print("TestViewController:onClick", target)
end

return TestViewController