
--------------------------------
-- @module MWSqliteDb
-- @extend MWObject,IDbBase
-- @parent_module mw

--------------------------------
-- 
-- @function [parent=#MWSqliteDb] executeNonQuery 
-- @param self
-- @param #string sql
-- @return bool#bool ret (return value: bool)
        
--------------------------------
-- 
-- @function [parent=#MWSqliteDb] endTransaction 
-- @param self
-- @param #bool result
-- @return bool#bool ret (return value: bool)
        
--------------------------------
-- IDbBase overrides.
-- @function [parent=#MWSqliteDb] executeQuery 
-- @param self
-- @param #string sql
-- @return MWArrayList#MWArrayList ret (return value: mw.MWArrayList)
        
--------------------------------
-- 
-- @function [parent=#MWSqliteDb] beginTransaction 
-- @param self
-- @return bool#bool ret (return value: bool)
        
--------------------------------
-- Open a sqlite3 db and return a db object.<br>
-- param dbPath Db file path.<br>
-- return SqliteDb object.
-- @function [parent=#MWSqliteDb] openDb 
-- @param self
-- @param #string dbPath
-- @return MWSqliteDb#MWSqliteDb ret (return value: mw.MWSqliteDb)
        
--------------------------------
-- Clear all connection cache.
-- @function [parent=#MWSqliteDb] clearConnectionCache 
-- @param self
        
return nil
