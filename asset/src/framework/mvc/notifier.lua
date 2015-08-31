--[[
	Description: Manage observers
	Author: M.Wan
	Date: 04/14/2014
]]

local Observer = class("Observer")

function Observer:ctor(sender, callback, ...)
	self._sender = sender
	self._callback = callback
	self._params = {...}
end

--[[ Seems that passing nil in "notify" function will cause exception. todo ]]
function Observer:call(...)
	local args = {...}
	for _, arg in ipairs(self._params) do
		table.insert(args, arg)
	end
	if self._callback then
		self._callback(self._sender, unpack(args))
	end
end



--[[
* Notifier is a machine which can send events but sender and observers don't need to know each other in the same context.
* @func addObserver add an observer who will care the event sent from the sender.
* @func removeObserver remove the observer who cares the event sent from the sender.
* @func notify send event with the event arguments.
]]
Notifier = {}

Notifier._observerMap = {}		-- observer map

function Notifier.addObserver(event, sender, callback, ...)
	assert(type(event) == "string", "Event name must be string type.")
	local observer = Observer.new(sender, callback, ...)
	if self.observer[event] == nil then
		self._observerMap[event] = {}
	end
	table.insert(self._observerMap[event], observer)
end

function Notifier.removeObserver(event, sender, callback)
	assert(type(event) == "string", "Event name must be string type.")
	if self._observerMap[event] == nil then
		return
	end
	local newObservers = {}
	for _, ob in ipairs(self._observerMap[event]) do
		if ob._sender == sender and (ob._callback == callback or callback == nil) then
		else
			table.insert(newObservers, ob)
		end
	end
	self._observerMap[event] = newObservers
end

function Notifier:notify(event, ...)
	assert(type(event) == "string", "Event name must be string type.")
	for k, v in pairs(self._observerMap) do
		if k == event then
			for _, ob in ipairs(v) do
				ob:call(unpack{...})
			end
			break
		end
	end
end