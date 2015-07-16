--[[
	Description: Internal objects extensions
	Author: M.Wan
	Date: 04/26/2014
]]

function mw.log(...)
	if DEBUG then
		print(os.date("%X"), string.format(...))
	end
end

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
function table.getTotalCount(table, selector, ...)
	if type(table) ~= "table" then
		return -1
	end
	
	local count = 0
	for k, v in pairs(table) do
		if selector == nil or selector(v, ...) then
			count = count + 1
		end
	end

	return count
end

-- concat strings with the specified character
function table.join(table, joinChar)
	if type(table) ~= "table" or type(joinChar) ~= "string" then
		return
	end

	local str = ""
	local count = 0
	for k, v in pairs(table) do
		str = str .. tostring(v)
		count = count + 1
		if count ~= #table then		
			str = str .. joinChar	
		end
	end
	return str
end

-- do action for each array element in table
function table.forEachAsArray(table, action)
	if type(table) ~= "table" or type(action) ~= "function" then
		return
	end

	for _, v in ipairs(table) do
		action(v)
	end
end

-- do action for each element in table
function table.forEachAsHash(table, action)
	if type(table) ~= "table" or type(action) ~= "function" then
		return
	end

	for k, v in pairs(table) do
		action(k, v)
	end
end

-- select new table for the specified behaviors
function table.select(table, selector, ...)
	if type(table) ~= "table" or type(selector) ~= "function" then
		return
	end

	local newTable = {}
	for _, v in ipairs(table) do
		if selector(v, ...) then
			_G["table"].insert(newTable, v)
		end
	end
	return newTable
end

-- cast every item of table to the specified item
function table.cast(table, caster, ...)
	if type(table) ~= "table" or type(caster) ~= "function" then
		return
	end

	local newTable = {}
	for _, v in ipairs(table) do
		local item = caster(v, ...)
		_G["table"].insert(newTable, item)
	end
	return newTable
end

-- whether the table contains the object which satisfies the condition
function table.contains(table, selector, ...)
	if type(table) ~= "table" then
		return false
	end

	for _, v in ipairs(table) do
		if selector(v, ...) then
			return true
		end
	end
	return false
end

-- find the object which satisfies the condition
function table.find(table, selector, ...)
	if type(table) ~= "table" then
		return false
	end

	for _, v in ipairs(table) do
		if selector(v, ...) then
			return v
		end
	end
	return nil
end

-- remove the object which satisfied the condition
function table.erase(table, selector, ...)
	if type(table) ~= "table" then
		return false
	end

	for i, v in ipairs(table) do
		if selector(v, ...) then
			_G["table"].remove(table, i)
			return true
		end
	end
	return false
end

-- random object which satisfied the condition
function table.random(table, selector, ...)
	if type(table) ~= "table" then
		return false
	end

	local targetTable = _G["table"].select(table, selector, ...)
	if #targetTable <= 0 then
		return nil
	end
	local rd = math.random(1, #targetTable)
	return targetTable[rd]
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
function table.serialize(table)
	if type(table) ~= "table" then
		return false
	end
	local mark = {}
	local assign = {}
	local function serialize_table(t, parent)
		mark[t] = parent
		local tmp = {}
		for k, v in pairs(t) do
			if (type(v) == "number" or type(v) == "string" or type(v) == "table" or type(v) == "boolean") and not string.find(k, "__") then
				local key = type(k) == "number" and "[" .. k .. "]" or k
				if type(v) == "table" then
					local dotKey = parent .. (type(k) == "number" and key or "." .. key)
					if mark[v] then
						_G["table"].insert(assign, dotKey .. "=" .. mark[v])
					else
						_G["table"].insert(tmp, key .. "=" .. serialize_table(v, dotKey))
					end
				else
					_G["table"].insert(tmp, key .. "=" .. (type(v) == "string" and ("\"" .. v .. "\"") or tostring(v)))
				end
			end
		end
		return "{" .. _G["table"].concat(tmp, ",") .. "}"
	end

	return "do local ret = " .. serialize_table(table, "ret") .. _G["table"].concat(assign, " ") .. " return ret end"
end

-- split string from the specified character
function string.split(str, splitChar)
	local resultTable = {}

	while true do
		local pos = string.find(str, splitChar)
		if not pos then
			table.insert(resultTable, str)
			break
		end
		local subStr = string.sub(str, 1, pos - 1)
		table.insert(resultTable, subStr)
		str = string.sub(str, pos + 1, #str)
	end

	return resultTable
end