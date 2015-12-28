
--------------------------------
-- @module MWNetResponse
-- @extend MWObject
-- @parent_module mw

--------------------------------
-- 
-- @function [parent=#MWNetResponse] getRelatedRequest 
-- @param self
-- @return MWNetRequest#MWNetRequest ret (return value: mw.MWNetRequest)
        
--------------------------------
-- 
-- @function [parent=#MWNetResponse] getProtocolId 
-- @param self
-- @return string#string ret (return value: string)
        
--------------------------------
-- 
-- @function [parent=#MWNetResponse] setBody 
-- @param self
-- @param #mw.MWBinaryData var
        
--------------------------------
-- 
-- @function [parent=#MWNetResponse] setProtocolId 
-- @param self
-- @param #string var
        
--------------------------------
-- 
-- @function [parent=#MWNetResponse] getBody 
-- @param self
-- @return MWBinaryData#MWBinaryData ret (return value: mw.MWBinaryData)
        
--------------------------------
-- Create a new MWNetResponse.<br>
-- param protocolId Protocol id.<br>
-- param body Request body.<br>
-- param request The request object related to the response.<br>
-- return Return a new NetRequest object.
-- @function [parent=#MWNetResponse] create 
-- @param self
-- @param #string protocolId
-- @param #mw.MWBinaryData body
-- @param #mw.MWNetRequest request
-- @return MWNetResponse#MWNetResponse ret (return value: mw.MWNetResponse)
        
return nil
