
--------------------------------
-- @module MWGameScene
-- @extend Scene
-- @parent_module mw

--------------------------------
-- 
-- @function [parent=#MWGameScene] getViewControllers 
-- @param self
-- @return MWDictionary#MWDictionary ret (return value: mw.MWDictionary)
        
--------------------------------
-- Unload an existed view controller of the scene.<br>
-- param controller The view controller to unload.
-- @function [parent=#MWGameScene] unloadViewController 
-- @param self
-- @param #mw.MWViewController controller
        
--------------------------------
-- Segue a view controller from the root view controller with the way of overlapping.<br>
-- note The behavior is to load a view controller as the child of the root view controller, so when you call this method, you should know what you are doing.<br>
-- param controller The view controller to load.
-- @function [parent=#MWGameScene] loadViewController 
-- @param self
-- @param #mw.MWViewController controller
-- @param #string identifier
        
--------------------------------
-- Get the loaded view controller by the specified identifier.<br>
-- return The view controller with specified identifier.
-- @function [parent=#MWGameScene] getViewControllerByIdentifier 
-- @param self
-- @param #string identifier
-- @return MWViewController#MWViewController ret (return value: mw.MWViewController)
        
--------------------------------
-- 
-- @function [parent=#MWGameScene] getBooleanParameter 
-- @param self
-- @param #string key
-- @return bool#bool ret (return value: bool)
        
--------------------------------
-- Unload all view controllers of the scene.
-- @function [parent=#MWGameScene] unloadAllViewControllers 
-- @param self
        
--------------------------------
-- @overload self, string, bool         
-- @overload self, string, double         
-- @overload self, string, string         
-- @overload self, string, cc.Ref         
-- @function [parent=#MWGameScene] addParameter
-- @param self
-- @param #string key
-- @param #cc.Ref param

--------------------------------
-- 
-- @function [parent=#MWGameScene] getRefParameter 
-- @param self
-- @param #string key
-- @return Ref#Ref ret (return value: cc.Ref)
        
--------------------------------
-- 
-- @function [parent=#MWGameScene] getMemoryWarningLine 
-- @param self
-- @return double#double ret (return value: double)
        
--------------------------------
-- 
-- @function [parent=#MWGameScene] setMemoryWarningLine 
-- @param self
-- @param #double var
        
--------------------------------
-- 
-- @function [parent=#MWGameScene] getStringParameter 
-- @param self
-- @param #string key
-- @return string#string ret (return value: string)
        
--------------------------------
-- Unload a view controller by the identifier.<br>
-- param identifier The view controller's identifier.
-- @function [parent=#MWGameScene] unloadViewControllerByIdentifier 
-- @param self
-- @param #string identifier
        
--------------------------------
-- Get the parameter of the specified key, it will throw an exception if the key doesn't exist.<br>
-- param key Parameter key to consult.<br>
-- return The parameter value.
-- @function [parent=#MWGameScene] getNumberParameter 
-- @param self
-- @param #string key
-- @return double#double ret (return value: double)
        
--------------------------------
-- Create a game scene.<br>
-- return MWGameScene instance which is autoreleased.
-- @function [parent=#MWGameScene] create 
-- @param self
-- @return MWGameScene#MWGameScene ret (return value: mw.MWGameScene)
        
return nil
