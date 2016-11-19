
--------------------------------
-- @module MWHttpGetService
-- @extend MWNetService
-- @parent_module mw

--------------------------------
-- 
-- @function [parent=#MWHttpGetService] executeCommand 
-- @param self
-- @param #string cmd
-- @param #cc.Ref param
        
--------------------------------
-- NetService overrides.
-- @function [parent=#MWHttpGetService] sendMessage 
-- @param self
-- @param #mw.MWNetRequest request
        
--------------------------------
-- Set service address.
-- @function [parent=#MWHttpGetService] setServiceAddress 
-- @param self
-- @param #string serviceAddress
        
--------------------------------
-- Get service address.
-- @function [parent=#MWHttpGetService] getServiceAddress 
-- @param self
-- @return string#string ret (return value: string)
        
--------------------------------
-- Create HttpGetService with specified service address.<br>
-- param serviceAddress Service address.
-- @function [parent=#MWHttpGetService] create 
-- @param self
-- @param #string serviceAddress
-- @return MWHttpGetService#MWHttpGetService ret (return value: mw.MWHttpGetService)
        
--------------------------------
-- HttpGetService constructor.<br>
-- param serviceAddress Service address.
-- @function [parent=#MWHttpGetService] MWHttpGetService 
-- @param self
-- @param #string serviceAddress
        
return nil
