--[[
	Description: Internal objects extensions
	Author: M.Wan
	Date: 04/26/2014
]]

-- Copy k-v from source table to the target table.
function table.shallowCopy(targetTable, sourceTable)
	if type(targetTable) == "table" and type(sourceTable) == "table" then
		for k, v in pairs(sourceTable) do
			targetTable[k] = v
		end
	end
end

-- Deep copy
function table.deepCopy(targetTable, sourceTable)
	if type(targetTable) == "table" and type(sourceTable) == "table" then
		for k, v in pairs(sourceTable) do
			if type(v) == "table" then
				if type(targetTable[k]) ~= "table" then
					targetTable[k] = {}
				end
				table.deepCopy(targetTable[k], v)
			else
				targetTable[k] = v
			end
		end
	end
end

-- get k-v count
function table.count(t, selector, ...)
	if type(t) ~= "table" then
		return -1
	end
	
	local count = 0
	for k, v in pairs(t) do
		if selector == nil or selector(v, k, ...) then
			count = count + 1
		end
	end

	return count
end

-- concat strings with the specified character
function table.join(t, c)
	if type(t) ~= "table" or type(c) ~= "string" then
		return
	end

	local str = ""
	for i, v in ipairs(t) do
		str = str .. tostring(v)
		if i ~= #t then		
			str = str .. c	
		end
	end
	return str
end

-- do action for each element in table
function table.forEach(t, action, ...)
	if type(t) ~= "table" or type(action) ~= "function" then
		return
	end

	for i, v in ipairs(t) do
		action(v, ...)
	end
end

-- select new table for the specified behaviors
function table.select(t, selector, ...)
	if type(t) ~= "table" or type(selector) ~= "function" then
		return nil
	end

	local ret = {}
	for i, v in ipairs(t) do
		ret[i] = selector(v, ...)
	end
	return ret
end

-- find elements which satisfy the selector
function table.filter(t, filter, ...)
	if type(t) ~= "table" or type(filter) ~= "function" then
		return nil
	end

	local ret = {}
	for i, v in ipairs(t) do
		if filter(v, ...) then
			table.insert(ret, v)
		end
	end
	return ret
end

-- whether the table contains the object which satisfies the condition
function table.contains(t, selector, ...)
	if type(t) ~= "table" then
		return false
	end

	for i, v in ipairs(t) do
		if selector(v, ...) then
			return true
		end
	end
	return false
end

-- remove the first object which satisfied the condition
function table.erase(t, selector, ...)
	if type(t) ~= "table" then
		return false
	end

	for i, v in ipairs(t) do
		if selector(v, ...) then
			table.remove(table, i)
			return true
		end
	end
	return false
end

-- reverse the table
function table.reverse(t)
	for i = 1, math.floor(#t / 2) do
		t[i], t[#t - i + 1] = t[#t - i + 1], t[i]
	end
end

-- shuffle the array
function table.shuffle(t)
	if type(t) ~= "table" then
		return
	end

	local rd = nil
	for i = 1, #t - 1 do
		rd = math.random(1, #t - i - 1)
		t[i], t[rd] = t[rd], t[i]
	end
end

-- log table
function table.dump(table)   
	if type(table) ~= "table" then
		return false
	end
    local function dump(data, prefix)
    	prefix = prefix or ""
		local str = tostring(data)
		local prefix_next = prefix .. "\t"
		str = str .. "\n" .. prefix .. "{"
		for k, v in pairs(data) do
			str = str .. "\n" .. prefix_next .. k .. " = "
			if type(v) == "table" then
				str = str .. dump(v, prefix_next)
			else
				str = str .. tostring(v)
			end
		end
		str = str .. "\n" .. prefix .. "}"
		return str
	end
	local traceback = string.split(debug.traceback("", 2), "\n")
	print("dump from: " .. string.trim(traceback[3]))
	print(dump(table))
end

-- serialze table
function table.serialize(t, filter, ...)
	if type(t) ~= "table" then
		return false
	end
	if filter == nil or type(filter) ~= "function" then
		filter = function()
			return true
		end
	end
	local mark = {}
	local assign = {}
	local function serialize_table(t, parent, filter, ...)
		mark[t] = parent
		local tmp = {}
		for k, v in pairs(t) do
			if (type(v) == "number" or type(v) == "string" or type(v) == "table" or type(v) == "boolean") and filter(v, k, ...) then
				local key = type(k) == "number" and "[" .. k .. "]" or k
				if type(v) == "table" then
					local dotKey = parent .. (type(k) == "number" and key or "." .. key)
					if mark[v] then
						table.insert(assign, dotKey .. "=" .. mark[v])
					else
						table.insert(tmp, key .. "=" .. serialize_table(v, dotKey))
					end
				else
					table.insert(tmp, key .. "=" .. (type(v) == "string" and ("\"" .. v .. "\"") or tostring(v)))
				end
			end
		end
		return "{" .. table.concat(tmp, ",") .. "}"
	end

	return "do local ret = " .. serialize_table(t, "ret", filter, ...) .. table.concat(assign, " ") .. " return ret end"
end

-- split string from the specified character
function string.split(s, delimiter)
    s = tostring(s)
    delimiter = tostring(delimiter)
    if (delimiter == "") then return nil end

    local pos, arr = 0, {}
    -- for each divider found
    for st, sp in function() return string.find(s, delimiter, pos, true) end do
        table.insert(arr, string.sub(s, pos, st - 1))
        pos = sp + 1
    end
    table.insert(arr, string.sub(s, pos))

    return arr
end

function string.ltrim(str)
	return string.gsub(str, "^[ \t\n\r]+", "")
end

function string.rtrim(str)
	return string.gsub(str, "[ \t\n\r]+$", "")
end

function string.trim(str)
	str = string.gsub(str, "^[ \t\n\r]+", "")
	return string.gsub(str, "[ \t\n\r]+$", "")
end

-- get utf-8 char array
function string.charArray(s)
	local function getBytesOfChar(idx)
		local byte = string.byte(s, idx)
		if bit.rshift(byte, 7) == 0x0 then
			return 1
		elseif bit.rshift(byte, 5) == 0x6 then
			return 2
		elseif bit.rshift(byte, 4) == 0xE then
			return 3
		elseif bit.rshift(byte, 3) == 0x1E then
			return 4
		elseif bit.rshift(byte, 2) == 0x3E then
			return 5
		elseif bit.rshift(byte, 1) == 0x7E then
			return 6
		end
		return 1
	end

	local ary = {}
	local start = 1
	local idx = 1
	while idx <= #str do
		idx = idx + getBytesOfChar(idx)
		local substr = string.sub(str, start, idx - 1)
		start = idx
		table.insert(ary, substr)
	end

	return ary
end