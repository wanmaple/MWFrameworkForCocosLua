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
		action(v, i, ...)
	end
end

-- select new table for the specified behaviors
function table.select(t, selector, ...)
	if type(t) ~= "table" or type(selector) ~= "function" then
		return nil
	end

	local ret = {}
	for i, v in ipairs(t) do
		if selector(v, i, ...) then
			table.insert(ret, v)
		end
	end
	return ret
end

-- cast every item of table to the specified item
function table.cast(t, caster, ...)
	if type(t) ~= "table" or type(caster) ~= "function" then
		return nil
	end

	local ret = {}
	for i, v in ipairs(table) do
		local item = caster(v, i, ...)
		table.insert(ret, item)
	end
	return ret
end

-- whether the table contains the object which satisfies the condition
function table.contains(t, selector, ...)
	if type(t) ~= "table" then
		return false
	end

	for i, v in ipairs(t) do
		if selector(v, i, ...) then
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
		if selector(v, i, ...) then
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
function string.split(input, delimiter)
    input = tostring(input)
    delimiter = tostring(delimiter)
    if (delimiter == "") then return nil end

    local pos, arr = 0, {}
    -- for each divider found
    for st, sp in function() return string.find(input, delimiter, pos, true) end do
        table.insert(arr, string.sub(input, pos, st - 1))
        pos = sp + 1
    end
    table.insert(arr, string.sub(input, pos))

    return arr
end