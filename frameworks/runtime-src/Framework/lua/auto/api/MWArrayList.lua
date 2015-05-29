
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
-- Overload methods to set new value at the specified index.<br>
-- note If the index is out of range, it will throw an exception.<br>
-- param val List value.<br>
-- param index List index.
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
-- Overload methods to append value to the list.<br>
-- param val List value to append.
-- @function [parent=#MWArrayList] appendObject 
-- @param self
-- @param #cc.Ref val
        
--------------------------------
-- Overload methods to get the last index of the specified value.<br>
-- note It will return -1 if it's not found.<br>
-- param obj Object to consult.<br>
-- return Consult result.
-- @function [parent=#MWArrayList] lastIndexOfObject 
-- @param self
-- @param #cc.Ref obj
-- @return unsigned int#unsigned int ret (return value: unsigned int)
        
--------------------------------
-- Overload methods to get the first index of the specified value.<br>
-- note It will return -1 if it's not found.<br>
-- param obj Object to consult.<br>
-- return Consult result.
-- @function [parent=#MWArrayList] indexOfObject 
-- @param self
-- @param #cc.Ref obj
-- @return unsigned int#unsigned int ret (return value: unsigned int)
        
--------------------------------
-- Overload methods to insert the value before the specified index.<br>
-- note If the index is out of range, it will throw an exception.<br>
-- param val List value to add.<br>
-- param index List index to insert.
-- @function [parent=#MWArrayList] insertObjectAtIndex 
-- @param self
-- @param #cc.Ref val
-- @param #unsigned int index
        
--------------------------------
-- Overload methods to remove specified object in the list.<br>
-- param obj Object to remove.<br>
-- return Remove result.
-- @function [parent=#MWArrayList] removeObject 
-- @param self
-- @param #cc.Ref obj
-- @return bool#bool ret (return value: bool)
        
--------------------------------
-- ICloneable overrides.
-- @function [parent=#MWArrayList] clone 
-- @param self
-- @return MWArrayList#MWArrayList ret (return value: mw.MWArrayList)
        
--------------------------------
-- Clear all objects.
-- @function [parent=#MWArrayList] clear 
-- @param self
        
--------------------------------
-- Whether the list is empty?
-- @function [parent=#MWArrayList] empty 
-- @param self
-- @return bool#bool ret (return value: bool)
        
--------------------------------
-- Get the value at the specified index, it will throw an exception if the key doesn't exist.<br>
-- param index List index.<br>
-- return List value at the index.
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
