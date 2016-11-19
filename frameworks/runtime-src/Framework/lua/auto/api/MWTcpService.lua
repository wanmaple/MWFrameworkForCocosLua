
--------------------------------
-- @module MWTcpService
-- @extend MWNetService
-- @parent_module mw

--------------------------------
-- 
-- @function [parent=#MWTcpService] executeCommand 
-- @param self
-- @param #string cmd
-- @param #cc.Ref param
        
--------------------------------
-- 
-- @function [parent=#MWTcpService] getPort 
-- @param self
-- @return int#int ret (return value: int)
        
--------------------------------
-- NetService overrides.
-- @function [parent=#MWTcpService] sendMessage 
-- @param self
-- @param #mw.MWNetRequest request
        
--------------------------------
-- 
-- @function [parent=#MWTcpService] getHost 
-- @param self
-- @return string#string ret (return value: string)
        
--------------------------------
-- 
-- @function [parent=#MWTcpService] create 
-- @param self
-- @param #string host
-- @param #int port
-- @param #string protocolId
-- @param #int bindPort
-- @return MWTcpService#MWTcpService ret (return value: mw.MWTcpService)
        
return nil
