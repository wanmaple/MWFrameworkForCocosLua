
--------------------------------
-- @module MWNetRequest
-- @extend MWObject
-- @parent_module mw

--------------------------------
-- 
-- @function [parent=#MWNetRequest] getProtocolId 
-- @param self
-- @return string#string ret (return value: string)
        
--------------------------------
-- 
-- @function [parent=#MWNetRequest] setBody 
-- @param self
-- @param #string var
        
--------------------------------
-- 
-- @function [parent=#MWNetRequest] setProtocolId 
-- @param self
-- @param #string var
        
--------------------------------
-- 
-- @function [parent=#MWNetRequest] getBody 
-- @param self
-- @return string#string ret (return value: string)
        
--------------------------------
-- Create a new NetRequest.<br>
-- param protocolId Protocol id.<br>
-- param body Request body.<br>
-- return Return a new NetRequest object.
-- @function [parent=#MWNetRequest] create 
-- @param self
-- @param #string protocolId
-- @param #string body
-- @return MWNetRequest#MWNetRequest ret (return value: mw.MWNetRequest)
        
return nil