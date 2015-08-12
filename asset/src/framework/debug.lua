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
		print("[" .. string.upper(tag) .. "]", string.format(fmt, ...))
	end
end

function logError(fmt, ...)
	if DEBUG then
		logWithTag("error", fmt, ...)
		print(debug.traceback("", 2))
	end
end

-- mark as deprecated
function deprecate(oldClass, newClass)
	assert(false, oldClass .. " is deprecated, use " .. newClass .. " instead.")
end