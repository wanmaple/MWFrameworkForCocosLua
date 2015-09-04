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

    local minX = math.min(math.min(topLeft.x, topRight.x), math.min(bottomLeft.x, bottomRight.x))
    local maxX = math.max(math.max(topLeft.x, topRight.x), math.max(bottomLeft.x, bottomRight.x))
    local minY = math.min(math.min(topLeft.y, topRight.y), math.min(bottomLeft.y, bottomRight.y))
    local maxY = math.max(math.max(topLeft.y, topRight.y), math.max(bottomLeft.y, bottomRight.y))

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