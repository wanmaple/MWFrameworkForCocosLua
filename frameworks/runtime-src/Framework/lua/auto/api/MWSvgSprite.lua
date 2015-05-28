
--------------------------------
-- @module MWSvgSprite
-- @extend Sprite
-- @parent_module mw

--------------------------------
-- 
-- @function [parent=#MWSvgSprite] setVectorScale 
-- @param self
-- @param #float scale
        
--------------------------------
-- 
-- @function [parent=#MWSvgSprite] getVectorScale 
-- @param self
-- @return float#float ret (return value: float)
        
--------------------------------
-- Create svg sprite by an svg vector image path.<br>
-- param svgPath SVG file path.<br>
-- param dpi Preferred dpi.
-- @function [parent=#MWSvgSprite] createWithFile 
-- @param self
-- @param #string svgPath
-- @param #float dpi
-- @return MWSvgSprite#MWSvgSprite ret (return value: mw.MWSvgSprite)
        
--------------------------------
-- Create svg sprite with binary data.<br>
-- param imgData SVG binary data.<br>
-- param dpi Preferred dpi.
-- @function [parent=#MWSvgSprite] createWithRawData 
-- @param self
-- @param #mw.MWBinaryData imgData
-- @param #float dpi
-- @return MWSvgSprite#MWSvgSprite ret (return value: mw.MWSvgSprite)
        
return nil
