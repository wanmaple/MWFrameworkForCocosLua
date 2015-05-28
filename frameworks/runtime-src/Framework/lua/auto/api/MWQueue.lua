
--------------------------------
-- @module MWQueue
-- @extend MWObject,ICloneable<mwframework::MWQueue>
-- @parent_module mw

--------------------------------
-- Get the elements count of the queue.
-- @function [parent=#MWQueue] count 
-- @param self
-- @return unsigned int#unsigned int ret (return value: unsigned int)
        
--------------------------------
-- Pop the front of the queue.<br>
-- note It will return false if the queue is empty.<br>
-- return Popped result.
-- @function [parent=#MWQueue] dequeue 
-- @param self
-- @return bool#bool ret (return value: bool)
        
--------------------------------
-- Clear all objects.
-- @function [parent=#MWQueue] clear 
-- @param self
        
--------------------------------
-- Insert new value to the queue back.<br>
-- param val Queue value.
-- @function [parent=#MWQueue] enqueue 
-- @param self
-- @param #cc.Ref val
        
--------------------------------
-- Get the front of queue.<br>
-- note It will return nullptr if the queue is empty.<br>
-- return The front of the queue.
-- @function [parent=#MWQueue] front 
-- @param self
-- @return Ref#Ref ret (return value: cc.Ref)
        
--------------------------------
-- ICloneable overrides.
-- @function [parent=#MWQueue] clone 
-- @param self
-- @return MWQueue#MWQueue ret (return value: mw.MWQueue)
        
--------------------------------
-- Whether the queue is empty?
-- @function [parent=#MWQueue] empty 
-- @param self
-- @return bool#bool ret (return value: bool)
        
--------------------------------
-- Create a queue structure.<br>
-- return MWQueue instance which is autoreleased.
-- @function [parent=#MWQueue] create 
-- @param self
-- @return MWQueue#MWQueue ret (return value: mw.MWQueue)
        
--------------------------------
-- MWQueue constructor.
-- @function [parent=#MWQueue] MWQueue 
-- @param self
        
return nil
