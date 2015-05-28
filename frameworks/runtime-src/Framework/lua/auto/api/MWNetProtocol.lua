
--------------------------------
-- @module MWNetProtocol
-- @extend MWObject,IUninheritable<mwframework::MWNetProtocol>
-- @parent_module mw

--------------------------------
-- 
-- @function [parent=#MWNetProtocol] getRelatedHandler 
-- @param self
-- @return MWNetHandler#MWNetHandler ret (return value: mw.MWNetHandler)
        
--------------------------------
-- 
-- @function [parent=#MWNetProtocol] getServiceId 
-- @param self
-- @return string#string ret (return value: string)
        
--------------------------------
-- 
-- @function [parent=#MWNetProtocol] getProtocolId 
-- @param self
-- @return string#string ret (return value: string)
        
--------------------------------
-- 
-- @function [parent=#MWNetProtocol] setServiceId 
-- @param self
-- @param #string var
        
--------------------------------
-- 
-- @function [parent=#MWNetProtocol] setProtocolId 
-- @param self
-- @param #string var
        
--------------------------------
-- Create a new NetProtocol.<br>
-- param protocolId Protocol id.<br>
-- param serviceId Service id.<br>
-- param handler Related net handler.<br>
-- return Return a new NetProtocol object.
-- @function [parent=#MWNetProtocol] create 
-- @param self
-- @param #string protocolId
-- @param #string serviceId
-- @param #mw.MWNetHandler handler
-- @return MWNetProtocol#MWNetProtocol ret (return value: mw.MWNetProtocol)
        
return nil
