class("TestViewController", clsViewController)

local winSize = cc.Director:getInstance():getWinSize()

function TestViewController:viewDidLoad()
	local zipData = mw.ZipData:createWithExistingFile("res/GIF/pokemon_gif5.rc")
	zipData:beginUnzip()
	local data1 = zipData:getCompressedFileData("487_o.gif", "7ujm,lp-")
	local data2 = zipData:getCompressedFileData("493.gif", "7ujm,lp-")
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
		sp:setPosition(winSize.width * (0.25 + (i - 1) * 0.5), winSize.height * 0.5)
		self:view():addChild(sp)

		-- local frames = sp:getFrames()
		-- for _, frame in ipairs(frames) do
		-- 	print("#####", tolua.type(frame), frame:getDuration())
		-- end
	end

	mw.log("NUMBER: %d", self:scene():getNumberParameter("NUMBER"))
	mw.log("STRING: %s", self:scene():getStringParameter("STRING"))
	mw.log("BOOLEAN: %s", tostring(self:scene():getBooleanParameter("BOOLEAN")))
	mw.log("REF: %s", GetType(self:scene():getRefParameter("REF")))

	local db = mw.SqliteDb:openDb("src/icon.jpg")
	local t = db:executeQuery("select * from [Vip]");
	-- table.dump(t)

	mw.log("UUID: %s", mw.UUIDGenerator:getInstance():generateUUID())
end

function TestViewController:viewDidUnload()

end