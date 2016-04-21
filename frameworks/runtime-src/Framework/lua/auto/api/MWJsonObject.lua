
--------------------------------
-- @module MWJsonObject
-- @extend MWObject
-- @parent_module mw

--------------------------------
-- Get pairs count of json.<br>
-- return Return the count of key-value pairs.
-- @function [parent=#MWJsonObject] count 
-- @param self
-- @return unsigned int#unsigned int ret (return value: unsigned int)
        
--------------------------------
-- Get json array of the specified key.<br>
-- param key Key to consult.<br>
-- return Return json array of key.
-- @function [parent=#MWJsonObject] getJsonArray 
-- @param self
-- @param #string key
-- @return MWJsonArray#MWJsonArray ret (return value: mw.MWJsonArray)
        
--------------------------------
-- Return boolean of the specified key.<br>
-- param key Key to consult.<br>
-- return Return boolean value of key.
-- @function [parent=#MWJsonObject] getBoolean 
-- @param self
-- @param #string key
-- @return bool#bool ret (return value: bool)
        
--------------------------------
-- Add new boolean value to json.<br>
-- param key Key to insert.<br>
-- param value Boolean value to add.
-- @function [parent=#MWJsonObject] putBoolean 
-- @param self
-- @param #string key
-- @param #bool value
        
--------------------------------
-- Return string of the specified key.<br>
-- param key Key to consult.<br>
-- return Return string value of key.
-- @function [parent=#MWJsonObject] getString 
-- @param self
-- @param #string key
-- @return char#char ret (return value: char)
        
--------------------------------
-- Return number of the specified key.<br>
-- param key Key to consult.<br>
-- return Return number value of key.
-- @function [parent=#MWJsonObject] getNumber 
-- @param self
-- @param #string key
-- @return double#double ret (return value: double)
        
--------------------------------
-- Convert to pretty string.<br>
-- return Return pretty version of json string.
-- @function [parent=#MWJsonObject] toPrettyString 
-- @param self
-- @return string#string ret (return value: string)
        
--------------------------------
-- Add new json array to json.<br>
-- param key Key to insert.<br>
-- param value Json array to add.
-- @function [parent=#MWJsonObject] putJsonArray 
-- @param self
-- @param #string key
-- @param #mw.MWJsonArray value
        
--------------------------------
-- Add new json object to json.<br>
-- param key Key to insert.<br>
-- param value Json object to add.
-- @function [parent=#MWJsonObject] putJsonObject 
-- @param self
-- @param #string key
-- @param #mw.MWJsonObject value
        
--------------------------------
-- Clear json.
-- @function [parent=#MWJsonObject] clear 
-- @param self
        
--------------------------------
-- Convert to lua string.<br>
-- return Return lua version of json string.
-- @function [parent=#MWJsonObject] toLuaString 
-- @param self
-- @return string#string ret (return value: string)
        
--------------------------------
-- Add new number value to json.<br>
-- param key Key to insert.<br>
-- param value Number value to add.
-- @function [parent=#MWJsonObject] putNumber 
-- @param self
-- @param #string key
-- @param #double value
        
--------------------------------
-- Remove value of the specified key.<br>
-- param key Key to remove.
-- @function [parent=#MWJsonObject] remove 
-- @param self
-- @param #string key
        
--------------------------------
-- Add new string value to json.<br>
-- param key Key to insert.<br>
-- param value String value to add.
-- @function [parent=#MWJsonObject] putString 
-- @param self
-- @param #string key
-- @param #string value
        
--------------------------------
-- Get json object of the specified key.<br>
-- param key Key to consult.<br>
-- return Return json object of key.
-- @function [parent=#MWJsonObject] getJsonObject 
-- @param self
-- @param #string key
-- @return MWJsonObject#MWJsonObject ret (return value: mw.MWJsonObject)
        
--------------------------------
-- Figure out whether json has the specified key.<br>
-- param key Key to consult.<br>
-- return Whether the key exists.
-- @function [parent=#MWJsonObject] hasKey 
-- @param self
-- @param #string key
-- @return bool#bool ret (return value: bool)
        
--------------------------------
-- Get any object of the specified key.<br>
-- param key Key to consult.<br>
-- return Return object of key.
-- @function [parent=#MWJsonObject] getObject 
-- @param self
-- @param #string key
-- @return MWObject#MWObject ret (return value: mw.MWObject)
        
--------------------------------
-- Create a json object from json file.<br>
-- param jsonPath Json file path.<br>
-- return Return a new json object.
-- @function [parent=#MWJsonObject] createWithFile 
-- @param self
-- @param #string jsonPath
-- @return MWJsonObject#MWJsonObject ret (return value: mw.MWJsonObject)
        
--------------------------------
-- 
-- @function [parent=#MWJsonObject] create 
-- @param self
-- @return MWJsonObject#MWJsonObject ret (return value: mw.MWJsonObject)
        
--------------------------------
-- Create a json object through string.<br>
-- param jsonStr Json string.<br>
-- return Return a new json object.
-- @function [parent=#MWJsonObject] createWithString 
-- @param self
-- @param #string jsonStr
-- @return MWJsonObject#MWJsonObject ret (return value: mw.MWJsonObject)
        
--------------------------------
-- Convert to json string.<br>
-- return Return json string format.
-- @function [parent=#MWJsonObject] toString 
-- @param self
-- @return string#string ret (return value: string)
        
return nil
