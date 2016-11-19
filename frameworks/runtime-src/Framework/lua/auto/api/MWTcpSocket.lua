
--------------------------------
-- @module MWTcpSocket
-- @extend Ref,ISocketProtocol
-- @parent_module mw

--------------------------------
-- 
-- @function [parent=#MWTcpSocket] receive 
-- @param self
-- @return MWBinaryData#MWBinaryData ret (return value: mw.MWBinaryData)
        
--------------------------------
-- 
-- @function [parent=#MWTcpSocket] bind 
-- @param self
-- @param #int port
-- @return bool#bool ret (return value: bool)
        
--------------------------------
-- 
-- @function [parent=#MWTcpSocket] send 
-- @param self
-- @param #mw.MWBinaryData data
-- @return int#int ret (return value: int)
        
--------------------------------
-- 
-- @function [parent=#MWTcpSocket] isConnected 
-- @param self
-- @return bool#bool ret (return value: bool)
        
--------------------------------
-- Overrides
-- @function [parent=#MWTcpSocket] connect 
-- @param self
-- @param #string host
-- @param #int port
-- @return bool#bool ret (return value: bool)
        
--------------------------------
-- 
-- @function [parent=#MWTcpSocket] close 
-- @param self
        
--------------------------------
-- 
-- @function [parent=#MWTcpSocket] getPort 
-- @param self
-- @return int#int ret (return value: int)
        
--------------------------------
-- 
-- @function [parent=#MWTcpSocket] listen 
-- @param self
-- @param #int count
-- @return bool#bool ret (return value: bool)
        
--------------------------------
-- 
-- @function [parent=#MWTcpSocket] getHost 
-- @param self
-- @return string#string ret (return value: string)
        
--------------------------------
-- 
-- @function [parent=#MWTcpSocket] getBindPort 
-- @param self
-- @return int#int ret (return value: int)
        
--------------------------------
-- 
-- @function [parent=#MWTcpSocket] create 
-- @param self
-- @return MWTcpSocket#MWTcpSocket ret (return value: mw.MWTcpSocket)
        
return nil
