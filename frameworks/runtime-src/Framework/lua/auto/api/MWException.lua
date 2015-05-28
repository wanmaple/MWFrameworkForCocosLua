
--------------------------------
-- @module MWException
-- @extend MWObject
-- @parent_module mw

--------------------------------
-- Get error code.<br>
-- return Error code of the exception.
-- @function [parent=#MWException] errorCode 
-- @param self
-- @return int#int ret (return value: int)
        
--------------------------------
-- 
-- @function [parent=#MWException] what 
-- @param self
-- @return char#char ret (return value: char)
        
--------------------------------
-- Create MWException object.<br>
-- param errCode Error code.<br>
-- param msg Error message.<br>
-- return MWException instance which is autoreleased.
-- @function [parent=#MWException] create 
-- @param self
-- @param #int errCode
-- @param #char msg
-- @return MWException#MWException ret (return value: mw.MWException)
        
--------------------------------
-- MWException constructor.<br>
-- param errCode Error code.<br>
-- param msg Error message.
-- @function [parent=#MWException] MWException 
-- @param self
-- @param #int errCode
-- @param #char msg
        
return nil
