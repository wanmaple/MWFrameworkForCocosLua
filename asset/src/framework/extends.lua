--[[
    Description: Extends objects.
    Author: M.Wan
    Date: 08/12/2015
]]

--[[
	Make object bindable to a component.
]]
function extend(target)
	assert(type(target) == "table", "Invalid param target.")

	target._components = {}

    function target:checkComponent(name)
        return self._components[name] ~= nil
    end

    function target:addComponent(name, ...)
        local componentClass = require(name)
        self._components[name] = componentClass.new(...)
        component:_bind(self)
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