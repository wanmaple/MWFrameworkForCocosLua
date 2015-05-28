
--------------------------------
-- @module MWNetCenter
-- @extend MWObject
-- @parent_module mw

--------------------------------
-- Add a new net service.<br>
-- param serviceId Service id to add.<br>
-- param service Service object.
-- @function [parent=#MWNetCenter] addNetService 
-- @param self
-- @param #string serviceId
-- @param #mw.MWNetService service
        
--------------------------------
-- Remove all filters.
-- @function [parent=#MWNetCenter] removeAllNetFilters 
-- @param self
        
--------------------------------
-- Add a new net filter.<br>
-- param filter Filter to add.
-- @function [parent=#MWNetCenter] addNetFilter 
-- @param self
-- @param #mw.MWNetFilter filter
        
--------------------------------
-- Remove the specified protocol.<br>
-- param protocolId Protocol id to remove.
-- @function [parent=#MWNetCenter] removeNetProtocol 
-- @param self
-- @param #string protocolId
        
--------------------------------
-- Remove net filter.<br>
-- param filter Filter to remove.
-- @function [parent=#MWNetCenter] removeNetFilter 
-- @param self
-- @param #mw.MWNetFilter filter
        
--------------------------------
-- Remove net service.<br>
-- param serviceId Service id to remove.
-- @function [parent=#MWNetCenter] removeNetService 
-- @param self
-- @param #string serviceId
        
--------------------------------
-- Send request to the server.<br>
-- param request The request to send.
-- @function [parent=#MWNetCenter] sendMessage 
-- @param self
-- @param #mw.MWNetRequest request
        
--------------------------------
-- @overload self, mw.MWNetProtocol         
-- @overload self, string, string, mw.MWNetHandler         
-- @function [parent=#MWNetCenter] addNetProtocol
-- @param self
-- @param #string protocolId
-- @param #string serviceId
-- @param #mw.MWNetHandler handler

--------------------------------
-- Dispatch the failed response.<br>
-- param response Returned response from the server.
-- @function [parent=#MWNetCenter] dispatchFailedMessage 
-- @param self
-- @param #mw.MWNetResponse response
        
--------------------------------
-- Dispatch the successful response.<br>
-- param response Returned response from the server.
-- @function [parent=#MWNetCenter] dispatchSuccessfulMessage 
-- @param self
-- @param #mw.MWNetResponse response
        
--------------------------------
-- Execute specified command.<br>
-- param serviceId Service id.<br>
-- param cmd Command name.<br>
-- param params Command parameters.
-- @function [parent=#MWNetCenter] sendCommand 
-- @param self
-- @param #string serviceId
-- @param #string cmd
-- @param #cc.Ref params
        
--------------------------------
-- 
-- @function [parent=#MWNetCenter] getInstance 
-- @param self
-- @return MWNetCenter#MWNetCenter ret (return value: mw.MWNetCenter)
        
return nil
