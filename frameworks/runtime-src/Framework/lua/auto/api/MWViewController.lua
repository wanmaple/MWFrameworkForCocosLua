
--------------------------------
-- @module MWViewController
-- @extend MWObject,IViewControllerDelegate
-- @parent_module mw

--------------------------------
-- Related segue getter and setter.
-- @function [parent=#MWViewController] segue 
-- @param self
-- @return MWViewSegue#MWViewSegue ret (return value: mw.MWViewSegue)
        
--------------------------------
-- Get admin scene.<br>
-- return Admin scene of the view controller.
-- @function [parent=#MWViewController] scene 
-- @param self
-- @return MWGameScene#MWGameScene ret (return value: mw.MWGameScene)
        
--------------------------------
-- Identifier getter and setter.
-- @function [parent=#MWViewController] getIdentifier 
-- @param self
-- @return string#string ret (return value: string)
        
--------------------------------
-- Get related view.<br>
-- return Related view of the view controller.
-- @function [parent=#MWViewController] view 
-- @param self
-- @return MWGameView#MWGameView ret (return value: mw.MWGameView)
        
--------------------------------
-- Create a view controller.<br>
-- param identifier View controller identifier maintained by the scene.<br>
-- return MWViewController instance which is autoreleased.
-- @function [parent=#MWViewController] create 
-- @param self
-- @return MWViewController#MWViewController ret (return value: mw.MWViewController)
        
return nil
