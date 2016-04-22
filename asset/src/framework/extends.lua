--[[
    Description: Extends objects.
    Author: M.Wan
    Date: 08/12/2015
]]

--[[
	Make object bindable to a component.
]]
function bindable(target)
	target._components = {}

    function target:checkComponent(name)
        return self._components[name] ~= nil
    end

    function target:addComponent(name, ...)
        local componentClass = require(name)
        local component = componentClass.new(...)
        component:_bind(self)
        self._components[name] = component
        return component
    end

    function target:removeComponent(name)
        local component = self._components[name]
        if component then component:_unbind() end
        self._components[name] = nil
    end

    function target:getComponent(name)
        return self._components[name]
    end

    return target
end

--[[
    Extend cc methods
]]
cc = cc or {}

function cc.pApplyAffineTransform(pt, t)
    local x = t.a * pt.x + t.c * pt.y + t.tx
    local y = t.b * pt.x + t.d * pt.y + t.ty 
    return cc.p(x, y)
end

function cc.rectApplyAffineTransform(rect, t)
    local top = cc.rectGetMinY(rect)
    local left = cc.rectGetMinX(rect)
    local right = cc.rectGetMaxX(rect)
    local bottom = cc.rectGetMaxY(rect)

    local topLeft = cc.pApplyAffineTransform(cc.p(left, top), t)
    local topRight = cc.pApplyAffineTransform(cc.p(right, top), t)
    local bottomLeft = cc.pApplyAffineTransform(cc.p(left, bottom), t)
    local bottomRight = cc.pApplyAffineTransform(cc.p(right, bottom), t)

    local minX = math.min(topLeft.x, topRight.x, bottomLeft.x, bottomRight.x)
    local maxX = math.max(topLeft.x, topRight.x, bottomLeft.x, bottomRight.x)
    local minY = math.min(topLeft.y, topRight.y, bottomLeft.y, bottomRight.y)
    local maxY = math.max(topLeft.y, topRight.y, bottomLeft.y, bottomRight.y)

    return cc.rect(minX, minY, (maxX - minX), (maxY - minY))
end

--[[
    Extend cc.Node
]]
local Node = cc.Node

function Node:getBoundingBoxToWorld()
    local boundingBox = self:getBoundingBox()
    local tran = self:getNodeToWorldAffineTransform()
    local bound = cc.rectApplyAffineTransform(boundingBox, tran)
    return bound
end

function Node:setColor(color)
    local func = tolua.getcfunction(self, "setColor")
    if type(color) == "string" then
        local hex = tonumber("0x" .. color)
        local r = math.floor(hex / 256 / 256) % 256
        local g = math.floor(hex / 256) % 256
        local b = math.mod(hex, 256)
        func(self, cc.c3b(r, g, b))
    else
        func(self, color)
    end
end