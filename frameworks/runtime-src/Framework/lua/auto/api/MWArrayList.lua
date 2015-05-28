
--------------------------------
-- @module MWArrayList
-- @extend MWObject,ICloneable<mwframework::MWArrayList>
-- @parent_module mw

--------------------------------
-- Get the elements count of the list.
-- @function [parent=#MWArrayList] count 
-- @param self
-- @return unsigned int#unsigned int ret (return value: unsigned int)
        
--------------------------------
-- @overload self, bool, unsigned int         
-- @overload self, double, unsigned int         
-- @overload self, string, unsigned int         
-- @overload self, cc.Ref, unsigned int         
-- @function [parent=#MWArrayList] setObjectAtIndex
-- @param self
-- @param #cc.Ref val
-- @param #unsigned int index

--------------------------------
-- Remove object at specified index, you will get a false if the index is out of range.<br>
-- param key List index to remove.<br>
-- return Remove result.
-- @function [parent=#MWArrayList] removeObjectAtIndex 
-- @param self
-- @param #unsigned int index
-- @return bool#bool ret (return value: bool)
        
--------------------------------
-- @overload self, bool         
-- @overload self, double         
-- @overload self, string         
-- @overload self, cc.Ref         
-- @function [parent=#MWArrayList] appendObject
-- @param self
-- @param #cc.Ref val

--------------------------------
-- @overload self, bool         
-- @overload self, double         
-- @overload self, string         
-- @overload self, cc.Ref         
-- @function [parent=#MWArrayList] lastIndexOfObject
-- @param self
-- @param #cc.Ref obj
-- @return unsigned int#unsigned int ret (return value: unsigned int)

--------------------------------
-- @overload self, bool         
-- @overload self, double         
-- @overload self, string         
-- @overload self, cc.Ref         
-- @function [parent=#MWArrayList] indexOfObject
-- @param self
-- @param #cc.Ref obj
-- @return unsigned int#unsigned int ret (return value: unsigned int)

--------------------------------
-- Clear all objects.
-- @function [parent=#MWArrayList] clear 
-- @param self
        
--------------------------------
-- ICloneable overrides.
-- @function [parent=#MWArrayList] clone 
-- @param self
-- @return MWArrayList#MWArrayList ret (return value: mw.MWArrayList)
        
--------------------------------
-- @overload self, bool, unsigned int         
-- @overload self, double, unsigned int         
-- @overload self, string, unsigned int         
-- @overload self, cc.Ref, unsigned int         
-- @function [parent=#MWArrayList] insertObjectAtIndex
-- @param self
-- @param #cc.Ref val
-- @param #unsigned int index

--------------------------------
-- Get the value at the specified index, it will throw an exception if the key doesn't exist.<br>
-- param index List index.<br>
-- return List value at the index.
-- @function [parent=#MWArrayList] numberAtIndex 
-- @param self
-- @param #unsigned int index
-- @return double#double ret (return value: double)
        
--------------------------------
-- @overload self, bool         
-- @overload self, double         
-- @overload self, string         
-- @overload self, cc.Ref         
-- @function [parent=#MWArrayList] removeObject
-- @param self
-- @param #cc.Ref obj
-- @return bool#bool ret (return value: bool)

--------------------------------
-- 
-- @function [parent=#MWArrayList] booleanAtIndex 
-- @param self
-- @param #unsigned int index
-- @return bool#bool ret (return value: bool)
        
--------------------------------
-- 
-- @function [parent=#MWArrayList] stringAtIndex 
-- @param self
-- @param #unsigned int index
-- @return string#string ret (return value: string)
        
--------------------------------
-- Whether the list is empty?
-- @function [parent=#MWArrayList] empty 
-- @param self
-- @return bool#bool ret (return value: bool)
        
--------------------------------
-- 
-- @function [parent=#MWArrayList] objectAtIndex 
-- @param self
-- @param #unsigned int index
-- @return Ref#Ref ret (return value: cc.Ref)
        
--------------------------------
-- Create an array structure.<br>
-- return MWArrayList instance which is autoreleased.
-- @function [parent=#MWArrayList] create 
-- @param self
-- @return MWArrayList#MWArrayList ret (return value: mw.MWArrayList)
        
--------------------------------
-- MWArrayList constructor.
-- @function [parent=#MWArrayList] MWArrayList 
-- @param self
        
return nil
