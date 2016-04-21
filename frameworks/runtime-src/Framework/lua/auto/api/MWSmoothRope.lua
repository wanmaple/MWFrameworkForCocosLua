
--------------------------------
-- @module MWSmoothRope
-- @extend Node
-- @parent_module mw

--------------------------------
-- @overload self, cc.Texture2D         
-- @overload self, string         
-- @function [parent=#MWSmoothRope] setSegmentTexture
-- @param self
-- @param #string path

--------------------------------
-- 
-- @function [parent=#MWSmoothRope] getSegments 
-- @param self
-- @return int#int ret (return value: int)
        
--------------------------------
-- 
-- @function [parent=#MWSmoothRope] setColor 
-- @param self
-- @param #color3b_table color
        
--------------------------------
-- 
-- @function [parent=#MWSmoothRope] getBending 
-- @param self
-- @return float#float ret (return value: float)
        
--------------------------------
-- 
-- @function [parent=#MWSmoothRope] setSegments 
-- @param self
-- @param #int segments
        
--------------------------------
-- 
-- @function [parent=#MWSmoothRope] setThickness 
-- @param self
-- @param #float thickness
        
--------------------------------
-- 
-- @function [parent=#MWSmoothRope] setBending 
-- @param self
-- @param #float val
        
--------------------------------
-- 
-- @function [parent=#MWSmoothRope] setOpacity 
-- @param self
-- @param #unsigned char opacity
        
--------------------------------
-- 
-- @function [parent=#MWSmoothRope] setTextureRect 
-- @param self
-- @param #rect_table var
        
--------------------------------
-- 
-- @function [parent=#MWSmoothRope] getSegmentTexture 
-- @param self
-- @return Texture2D#Texture2D ret (return value: cc.Texture2D)
        
--------------------------------
-- 
-- @function [parent=#MWSmoothRope] getThickness 
-- @param self
-- @return float#float ret (return value: float)
        
--------------------------------
-- 
-- @function [parent=#MWSmoothRope] getLength 
-- @param self
-- @return float#float ret (return value: float)
        
--------------------------------
-- 
-- @function [parent=#MWSmoothRope] setLength 
-- @param self
-- @param #float length
        
--------------------------------
-- 
-- @function [parent=#MWSmoothRope] setEndPoints 
-- @param self
-- @param #vec2_table end1
-- @param #vec2_table end2
        
--------------------------------
-- 
-- @function [parent=#MWSmoothRope] getTextureRect 
-- @param self
-- @return rect_table#rect_table ret (return value: rect_table)
        
--------------------------------
-- 
-- @function [parent=#MWSmoothRope] create 
-- @param self
-- @param #float length
-- @param #float thickness
-- @param #int segments
-- @return MWSmoothRope#MWSmoothRope ret (return value: mw.MWSmoothRope)
        
return nil
