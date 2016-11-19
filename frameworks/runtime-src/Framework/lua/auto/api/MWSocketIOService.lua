
--------------------------------
-- @module MWSocketIOService
-- @extend MWNetService,SIODelegate
-- @parent_module mw

--------------------------------
-- 
-- @function [parent=#MWSocketIOService] setServiceAddress 
-- @param self
-- @param #string var
        
--------------------------------
-- 
-- @function [parent=#MWSocketIOService] executeCommand 
-- @param self
-- @param #string cmd
-- @param #cc.Ref param
        
--------------------------------
-- NetService overrides.
-- @function [parent=#MWSocketIOService] sendMessage 
-- @param self
-- @param #mw.MWNetRequest request
        
--------------------------------
-- 
-- @function [parent=#MWSocketIOService] getServiceAddress 
-- @param self
-- @return string#string ret (return value: string)
        
--------------------------------
-- 
-- @function [parent=#MWSocketIOService] create 
-- @param self
-- @param #string serviceAddress
-- @param #string protocolId
-- @return MWSocketIOService#MWSocketIOService ret (return value: mw.MWSocketIOService)
        
return nil
