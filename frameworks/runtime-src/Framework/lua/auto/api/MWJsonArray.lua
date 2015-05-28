
--------------------------------
-- @module MWJsonArray
-- @extend MWObject
-- @parent_module mw

--------------------------------
-- Get json elements count of array.<br>
-- return Return the count of array.
-- @function [parent=#MWJsonArray] count 
-- @param self
-- @return unsigned int#unsigned int ret (return value: unsigned int)
        
--------------------------------
-- Get any object at specified index.<br>
-- param index Index to consult.<br>
-- return Specified value.
-- @function [parent=#MWJsonArray] getObjectAt 
-- @param self
-- @param #unsigned int index
-- @return MWObject#MWObject ret (return value: mw.MWObject)
        
--------------------------------
-- Convert to pretty string.<br>
-- return Return pretty version of json string.
-- @function [parent=#MWJsonArray] toPrettyString 
-- @param self
-- @return string#string ret (return value: string)
        
--------------------------------
-- Get string value at specified index.<br>
-- param index Index to consult.<br>
-- return Specified value.
-- @function [parent=#MWJsonArray] getStringAt 
-- @param self
-- @param #unsigned int index
-- @return char#char ret (return value: char)
        
--------------------------------
-- Insert a json array at the specified index.<br>
-- param value Json array.<br>
-- param index Specified index.
-- @function [parent=#MWJsonArray] insertJsonArray 
-- @param self
-- @param #mw.MWJsonArray value
-- @param #unsigned int index
        
--------------------------------
-- Append a json array to the array tail.<br>
-- param value Json array.
-- @function [parent=#MWJsonArray] appendJsonArray 
-- @param self
-- @param #mw.MWJsonArray value
        
--------------------------------
-- Insert a json object at the specified index.<br>
-- param value Json object.<br>
-- param index Specified index.
-- @function [parent=#MWJsonArray] insertJsonObject 
-- @param self
-- @param #mw.MWJsonObject value
-- @param #unsigned int index
        
--------------------------------
-- Clear all array elements.
-- @function [parent=#MWJsonArray] clear 
-- @param self
        
--------------------------------
-- Append a json object to the array tail.<br>
-- param value Json object.
-- @function [parent=#MWJsonArray] appendJsonObject 
-- @param self
-- @param #mw.MWJsonObject value
        
--------------------------------
-- Insert a number value at the specified index.<br>
-- param value Number value.<br>
-- param index Specified index.
-- @function [parent=#MWJsonArray] insertNumber 
-- @param self
-- @param #double value
-- @param #unsigned int index
        
--------------------------------
-- Remove the object at specified index.<br>
-- param index Index to remove.
-- @function [parent=#MWJsonArray] removeAt 
-- @param self
-- @param #unsigned int index
        
--------------------------------
-- Append a number value to the array tail.<br>
-- param value Number value.
-- @function [parent=#MWJsonArray] appendNumber 
-- @param self
-- @param #double value
        
--------------------------------
-- Append a boolean value to the array tail.<br>
-- param value Boolean value.
-- @function [parent=#MWJsonArray] appendBoolean 
-- @param self
-- @param #bool value
        
--------------------------------
-- Convert to lua string.<br>
-- return Return lua version of json string.
-- @function [parent=#MWJsonArray] toLuaString 
-- @param self
-- @return string#string ret (return value: string)
        
--------------------------------
-- Get boolean value at specified index.<br>
-- param index Index to consult.<br>
-- return Specified value.
-- @function [parent=#MWJsonArray] getBooleanAt 
-- @param self
-- @param #int index
-- @return bool#bool ret (return value: bool)
        
--------------------------------
-- Insert a string value at the specified index.<br>
-- param value String value.<br>
-- param index Specified index.
-- @function [parent=#MWJsonArray] insertString 
-- @param self
-- @param #string value
-- @param #int index
        
--------------------------------
-- Get json array at specified index.<br>
-- param index Index to consult.<br>
-- return Specified value.
-- @function [parent=#MWJsonArray] getJsonArrayAt 
-- @param self
-- @param #unsigned int index
-- @return MWJsonArray#MWJsonArray ret (return value: mw.MWJsonArray)
        
--------------------------------
-- Append a string value to the array tail.<br>
-- param value String value.
-- @function [parent=#MWJsonArray] appendString 
-- @param self
-- @param #string value
        
--------------------------------
-- Insert a boolean value at the specified index.<br>
-- param value Boolean value.<br>
-- param index Specified index.
-- @function [parent=#MWJsonArray] insertBoolean 
-- @param self
-- @param #bool value
-- @param #unsigned int index
        
--------------------------------
-- Get number value at specified index.<br>
-- param index Index to consult.<br>
-- return Specified value.
-- @function [parent=#MWJsonArray] getNumberAt 
-- @param self
-- @param #unsigned int index
-- @return double#double ret (return value: double)
        
--------------------------------
-- Get json object at specified index.<br>
-- param index Index to consult.<br>
-- return Specified value.
-- @function [parent=#MWJsonArray] getJsonObjectAt 
-- @param self
-- @param #unsigned int index
-- @return MWJsonObject#MWJsonObject ret (return value: mw.MWJsonObject)
        
--------------------------------
-- Create a json array from json file.<br>
-- param jsonPath Json file path.<br>
-- return Return a new json array.
-- @function [parent=#MWJsonArray] createWithFile 
-- @param self
-- @param #string jsonPath
-- @return MWJsonArray#MWJsonArray ret (return value: mw.MWJsonArray)
        
--------------------------------
-- 
-- @function [parent=#MWJsonArray] create 
-- @param self
-- @return MWJsonArray#MWJsonArray ret (return value: mw.MWJsonArray)
        
--------------------------------
-- Create a json array through string.<br>
-- param jsonStr Json string.<br>
-- return Return a new json array.
-- @function [parent=#MWJsonArray] createWithString 
-- @param self
-- @param #string jsonStr
-- @return MWJsonArray#MWJsonArray ret (return value: mw.MWJsonArray)
        
--------------------------------
-- Convert to json string.<br>
-- return Return json string format.
-- @function [parent=#MWJsonArray] toString 
-- @param self
-- @return string#string ret (return value: string)
        
return nil
