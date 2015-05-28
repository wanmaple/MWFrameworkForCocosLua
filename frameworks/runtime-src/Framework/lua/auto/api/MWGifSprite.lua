
--------------------------------
-- @module MWGifSprite
-- @extend Sprite
-- @parent_module mw

--------------------------------
-- Play the animation.<br>
-- param count How many times would you want to play the animation? It will play forever if the count is set to 0.
-- @function [parent=#MWGifSprite] play 
-- @param self
        
--------------------------------
-- Pause the animation.
-- @function [parent=#MWGifSprite] pause 
-- @param self
        
--------------------------------
-- 
-- @function [parent=#MWGifSprite] setSpeedRatio 
-- @param self
-- @param #float var
        
--------------------------------
-- 
-- @function [parent=#MWGifSprite] getSpriteFrameAtIndex 
-- @param self
-- @param #int index
-- @return SpriteFrame#SpriteFrame ret (return value: cc.SpriteFrame)
        
--------------------------------
-- Resume the animation.
-- @function [parent=#MWGifSprite] resume 
-- @param self
        
--------------------------------
-- 
-- @function [parent=#MWGifSprite] getSpeedRatio 
-- @param self
-- @return float#float ret (return value: float)
        
--------------------------------
-- Stop the animation, the sprite will display the first texture.
-- @function [parent=#MWGifSprite] stop 
-- @param self
        
--------------------------------
-- 
-- @function [parent=#MWGifSprite] getFrames 
-- @param self
-- @return MWArrayList#MWArrayList ret (return value: mw.MWArrayList)
        
--------------------------------
-- Create gif sprite by a gif image path.<br>
-- param gifPath GIF file path.
-- @function [parent=#MWGifSprite] createWithFile 
-- @param self
-- @param #string gifPath
-- @return MWGifSprite#MWGifSprite ret (return value: mw.MWGifSprite)
        
--------------------------------
-- Create gif sprite with frames.<br>
-- param frames GIF frames array.
-- @function [parent=#MWGifSprite] createWithFrames 
-- @param self
-- @param #mw.MWArrayList frames
-- @return MWGifSprite#MWGifSprite ret (return value: mw.MWGifSprite)
        
--------------------------------
-- Create gif sprite with binary data.<br>
-- param imgData GIF binary data.
-- @function [parent=#MWGifSprite] createWithRawData 
-- @param self
-- @param #mw.MWBinaryData imgData
-- @return MWGifSprite#MWGifSprite ret (return value: mw.MWGifSprite)
        
--------------------------------
-- 
-- @function [parent=#MWGifSprite] update 
-- @param self
-- @param #float dt
        
return nil
