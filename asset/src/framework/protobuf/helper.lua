--[[
    Description: To avoid some problems of pbc
    Author: M.Wan
    Date: 03/04/2016
]]

pb = pb or {}

pb.Helper = {}

local Helper = pb.Helper

function Helper.getNestedMsg(parentMsg, attrName)
	return protobuf.decode(parentMsg[attrName][1], parentMsg[attrName][2])
end

function Helper.getAttrIfExists(msg, attrName)
	return rawget(msg, attrName)
end