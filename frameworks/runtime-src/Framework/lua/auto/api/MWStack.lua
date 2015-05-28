
--------------------------------
-- @module MWStack
-- @extend MWObject,ICloneable<mwframework::MWStack>
-- @parent_module mw

--------------------------------
-- Get the elements count of the stack.
-- @function [parent=#MWStack] count 
-- @param self
-- @return unsigned int#unsigned int ret (return value: unsigned int)
        
--------------------------------
-- Get the top of the stack.<br>
-- note It will return nullptr if the stack is empty.<br>
-- return The top of the stack.
-- @function [parent=#MWStack] top 
-- @param self
-- @return Ref#Ref ret (return value: cc.Ref)
        
--------------------------------
-- Pop the top the stack.<br>
-- note It will return false if the stack is empty.<br>
-- return Popped result.
-- @function [parent=#MWStack] pop 
-- @param self
-- @return bool#bool ret (return value: bool)
        
--------------------------------
-- Push value to the stack top.<br>
-- param val Stack value.
-- @function [parent=#MWStack] push 
-- @param self
-- @param #cc.Ref val
        
--------------------------------
-- ICloneable overrides.
-- @function [parent=#MWStack] clone 
-- @param self
-- @return MWStack#MWStack ret (return value: mw.MWStack)
        
--------------------------------
-- Clear all objects.
-- @function [parent=#MWStack] clear 
-- @param self
        
--------------------------------
-- Whether the stack is empty?
-- @function [parent=#MWStack] empty 
-- @param self
-- @return bool#bool ret (return value: bool)
        
--------------------------------
-- Create a stack structure.<br>
-- return MWStack instance which is autoreleased.
-- @function [parent=#MWStack] create 
-- @param self
-- @return MWStack#MWStack ret (return value: mw.MWStack)
        
--------------------------------
-- MWStack constructor.
-- @function [parent=#MWStack] MWStack 
-- @param self
        
return nil
