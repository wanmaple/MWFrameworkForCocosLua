
--------------------------------
-- @module MWSystemHelper
-- @parent_module mw

--------------------------------
-- Get the current net status.
-- @function [parent=#MWSystemHelper] checkNetStatus 
-- @param self
-- @return int#int ret (return value: int)
        
--------------------------------
-- Get the current memory occupation (MB).<br>
-- return The memory occupied by the current process.
-- @function [parent=#MWSystemHelper] getCurrentUsedMemory 
-- @param self
-- @return double#double ret (return value: double)
        
--------------------------------
-- Get the current timestamp of ms unit.<br>
-- param content The content to copy.
-- @function [parent=#MWSystemHelper] millisecondsNow 
-- @param self
-- @return unsigned long#unsigned long ret (return value: unsigned long)
        
--------------------------------
-- Copy the content to the system paste board.<br>
-- param content The content to copy.
-- @function [parent=#MWSystemHelper] copyToPasteBoard 
-- @param self
-- @param #string content
        
--------------------------------
-- 
-- @function [parent=#MWSystemHelper] getInstance 
-- @param self
-- @return MWSystemHelper#MWSystemHelper ret (return value: mw.MWSystemHelper)
        
return nil
