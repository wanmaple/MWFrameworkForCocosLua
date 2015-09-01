
local TestViewController = class("TestViewController", function()
	return mw.ViewController:create()
end)

function TestViewController:viewDidLoad()
	log("Test GameScene parameters...")
	log("NUMBER: %d", self:scene():getNumberParameter("NUMBER"))
	log("STRING: %s", self:scene():getStringParameter("STRING"))
	log("BOOLEAN: %s", tostring(self:scene():getBooleanParameter("BOOLEAN")))
	log("REF: %s", GetType(self:scene():getRefParameter("REF")))

	log("Test ZipData and GifSprite...")
	local zipData = mw.ZipData:createWithExistingFile("res/GIF/pokemon_gif5.rc", "7ujm,lp-")
	zipData:beginUnzip()
	local data1 = zipData:getCompressedFileData("487_o.gif")
	local data2 = zipData:getCompressedFileData("493.gif")
	zipData:endUnzip()
	local gif1 = mw.GifSprite:createWithRawData(data1)
	local gif2 = mw.GifSprite:createWithRawData(data2)

	local pDict = mw.Dictionary:create()
	pDict:setObjectForKey("GIF1", gif1)
	pDict:setObjectForKey("GIF2", gif2)

	local keys = pDict:allKeys()
	for i, key in ipairs(keys) do
		local sp = pDict:objectForKey(key)
		tolua.cast(sp, "mw.GifSprite")
		sp:setPosition(Device:width() * (0.25 + (i - 1) * 0.5), Device:height() * 0.5)
		self:view():addChild(sp)
	end

    local svg = mw.SvgSprite:createWithFile("tiger.svg")
    svg:setPosition(Device:cx(), Device:cy())
    svg:setVectorScale(0.5)
    self:view():addChild(svg)

	log("Test Sqlite DB...")
	local db = mw.SqliteDb:openDb("res/icon.jpg")
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
end

function TestViewController:viewDidUnload()

end

return TestViewController