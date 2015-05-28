
--------------------------------
-- @module MWDictionary
-- @extend MWObject,ICloneable<mwframework::MWDictionary>
-- @parent_module mw

--------------------------------
-- Get the pairs count of the map.
-- @function [parent=#MWDictionary] count 
-- @param self
-- @return unsigned int#unsigned int ret (return value: unsigned int)
        
--------------------------------
-- Remove the pair of the specified key, you will get a false if there is no such key.<br>
-- param key Dictionary key to remove.<br>
-- return Remove result.
-- @function [parent=#MWDictionary] removeObjectForKey 
-- @param self
-- @param #string key
-- @return bool#bool ret (return value: bool)
        
--------------------------------
-- Clear all objects of the map.
-- @function [parent=#MWDictionary] clear 
-- @param self
        
--------------------------------
-- @overload self, string, bool         
-- @overload self, string, double         
-- @overload self, string, string         
-- @overload self, string, cc.Ref         
-- @function [parent=#MWDictionary] setObjectForKey
-- @param self
-- @param #string key
-- @param #cc.Ref val

--------------------------------
-- Whether the map is empty?
-- @function [parent=#MWDictionary] empty 
-- @param self
-- @return bool#bool ret (return value: bool)
        
--------------------------------
-- 
-- @function [parent=#MWDictionary] objectForKey 
-- @param self
-- @param #string key
-- @return Ref#Ref ret (return value: cc.Ref)
        
--------------------------------
-- ICloneable overrides.
-- @function [parent=#MWDictionary] clone 
-- @param self
-- @return MWDictionary#MWDictionary ret (return value: mw.MWDictionary)
        
--------------------------------
-- 
-- @function [parent=#MWDictionary] booleanForKey 
-- @param self
-- @param #string key
-- @return bool#bool ret (return value: bool)
        
--------------------------------
-- 
-- @function [parent=#MWDictionary] stringForKey 
-- @param self
-- @param #string key
-- @return string#string ret (return value: string)
        
--------------------------------
-- Whether the map contains the specified key?
-- @function [parent=#MWDictionary] hasKey 
-- @param self
-- @param #string key
-- @return bool#bool ret (return value: bool)
        
--------------------------------
-- Get the value of the specified key, it will throw an exception if the key doesn't exist.<br>
-- param key Dictionary key to consult.<br>
-- return Dictionary value.
-- @function [parent=#MWDictionary] numberForKey 
-- @param self
-- @param #string key
-- @return double#double ret (return value: double)
        
--------------------------------
-- Create a dictionary structure.<br>
-- return MWDictionary instance which is autoreleased.
-- @function [parent=#MWDictionary] create 
-- @param self
-- @return MWDictionary#MWDictionary ret (return value: mw.MWDictionary)
        
--------------------------------
-- MWDictionary constructor.
-- @function [parent=#MWDictionary] MWDictionary 
-- @param self
        
return nil
