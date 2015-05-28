
--------------------------------
-- @module MWGifFramesCache
-- @extend MWObject,IUninheritable<mwframework::MWGifFramesCache>
-- @parent_module mw

--------------------------------
-- Remove all gif cache.
-- @function [parent=#MWGifFramesCache] removeAll 
-- @param self
        
--------------------------------
-- @overload self, mw.MWBinaryData, string         
-- @overload self, string         
-- @overload self, mw.MWGifSprite, string         
-- @overload self, mw.MWArrayList, string         
-- @function [parent=#MWGifFramesCache] addGifFramesCache
-- @param self
-- @param #mw.MWArrayList frames
-- @param #string key

--------------------------------
-- Get the gif sprite from the specified key.<br>
-- param key Cached key.
-- @function [parent=#MWGifFramesCache] getGifSprite 
-- @param self
-- @param #string key
-- @return MWGifSprite#MWGifSprite ret (return value: mw.MWGifSprite)
        
--------------------------------
-- Remove the gif cache.<br>
-- param key The related key to remove.
-- @function [parent=#MWGifFramesCache] removeGifFramesCache 
-- @param self
-- @param #string key
        
--------------------------------
-- 
-- @function [parent=#MWGifFramesCache] getInstance 
-- @param self
-- @return MWGifFramesCache#MWGifFramesCache ret (return value: mw.MWGifFramesCache)
        
return nil
