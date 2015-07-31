--[[
	Description: For debug and log
	Author: M.Wan
	Date: 04/30/2014
]]

function log(fmt, ...)
	if DEBUG then
		print(os.date("%X"), string.format(fmt, ...))
	end
end

function logWithTag(tag, fmt, ...)
	if DEBUG then
		print(string.upper(tag), string.format(fmt, ...))
	end
end