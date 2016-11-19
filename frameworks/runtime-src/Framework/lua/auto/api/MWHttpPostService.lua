
--------------------------------
-- @module MWHttpPostService
-- @extend MWNetService
-- @parent_module mw

--------------------------------
-- 
-- @function [parent=#MWHttpPostService] executeCommand 
-- @param self
-- @param #string cmd
-- @param #cc.Ref param
        
--------------------------------
-- NetService overrides.
-- @function [parent=#MWHttpPostService] sendMessage 
-- @param self
-- @param #mw.MWNetRequest request
        
--------------------------------
-- Set service address.
-- @function [parent=#MWHttpPostService] setServiceAddress 
-- @param self
-- @param #string serviceAddress
        
--------------------------------
-- Get service address.
-- @function [parent=#MWHttpPostService] getServiceAddress 
-- @param self
-- @return string#string ret (return value: string)
        
--------------------------------
-- Create MWHttpPostService with specified service address.<br>
-- param serviceAddress Service address.
-- @function [parent=#MWHttpPostService] create 
-- @param self
-- @param #string serviceAddress
-- @return MWHttpPostService#MWHttpPostService ret (return value: mw.MWHttpPostService)
        
--------------------------------
-- MWHttpPostService constructor.<br>
-- param serviceAddress Service address.
-- @function [parent=#MWHttpPostService] MWHttpPostService 
-- @param self
-- @param #string serviceAddress
        
return nil
