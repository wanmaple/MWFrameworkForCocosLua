--[[
	Description: Manage observers
	Author: M.Wan
	Date: 04/14/2014
]]

luaclass("Observer")

Observer.sender = nil		-- notifier 
Observer.callback = nil		-- callback
Observer.params = nil		-- params, a table

--[[ Seems that passing nil in "notify" function will cause exception. todo ]]
function Observer:call(...)
	local args = {...}
	for _, arg in ipairs(self.params) do
		table.insert(args, arg)
	end
	if self.callback then
		self.callback(self.sender, unpack(args))
	end
end


-- static
Notifier = {}

Notifier.observerMap = {}		-- observer map

function Notifier:addObserver(event, sender, callback, ...)
	log("Notifier:addObserver", event, sender.__className)
	local observer = Observer:new()
	observer.sender = sender
	observer.callback = callback
	observer.params = {...}

	if not self.observerMap[event] then
		self.observerMap[event] = {}
	end
	table.insert(self.observerMap[event], observer)
end

function Notifier:removeObserver(event, sender)
	log("Notifier:removeObserver", event, sender.__className)
	if not self.observerMap[event] then
		return
	end
	local newObservers = {}
	for i, observer in ipairs(self.observerMap[event]) do
		if observer.sender ~= sender then
			table.insert(newObservers, observer)
		end
	end
	if #newObservers <= 0 then
		newObservers = nil
	end
	self.observerMap[event] = newObservers
end

function Notifier:notify(event, ...)
	-- log("Notifier:notify", event)
	for k, v in pairs(self.observerMap) do
		if k == event then
			for _, observer in ipairs(v) do
				observer:call(unpack{...})
			end
			break
		end
	end
end