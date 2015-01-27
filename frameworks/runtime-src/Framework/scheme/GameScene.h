/******************************
 Description: Game base scene
 Author: M.Wan
 Date: 1/28/2015
 ******************************/

#ifndef __SCHEME_GAME_SCENE__
#define __SCHEME_GAME_SCENE__

#include "base/CCRef.h"
#include "base/CCVector.h"
#include "base/CCMap.h"
#include "2d/CCScene.h"
#include "../base/Macros.h"
#include <map>
#include <string>

namespace mwframework {
    class ViewController;
    
    /**
     * Basic game scene of the framework.
     */
    class MWDLL GameScene : public cocos2d::Scene
    {
    public:
        /**
         * Create a game scene.
         *
         * @return GameScene instance which is autoreleased.
         */
        static GameScene *create();
        /**
         * Create a game scene with user params.
         *
         * @param params User parameters to pass to the scene.
         *
         * @return GameScene instance with params which is autoreleased.
         */
        static GameScene *createWithParams(const cocos2d::Map<std::string, cocos2d::Ref*> &params);
        
        /**
         * Base class overrides.
         */
        virtual void onEnter() override;
        virtual void onExit() override;
        
        /**
         * Overload methods to put new parameter to the scene.
         * @note If the key is already existed, the new parameter will override the old one.
         *
         * @param key New parameter key.
         * @param param It can be a number, boolean, string and cocos2dx object.
         */
        void addParameter(const std::string &key, double param);
        void addParameter(const std::string &key, bool param);
        void addParameter(const std::string &key, const std::string &param);
        void addParameter(const std::string &key, cocos2d::Ref *param);
        
        /**
         * Get the parameter of the specified key, return nullptr or default value if it doesn't exist.
         *
         * @param key Parameter key to consult.
         *
         * @return The parameter value.
         */
        double getNumberParameter(const std::string &key) const;
        bool getBooleanParameter(const std::string &key) const;
        std::string getStringParameter(const std::string &key) const;
        cocos2d::Ref *getRefParameter(const std::string &key) const;
        
        /**
         * Load a view controller to the scene.
         *
         * @param controller The view controller to load.
         */
        void loadViewController(ViewController *controller);
        /**
         * Unload an existed view controller of the scene.
         *
         * @param controller The view controller to unload.
         */
        void unloadViewController(ViewController *controller);
        /**
         * Unload a view controller by the identifier.
         *
         * @param identifier The view controller's identifier.
         */
        void unloadViewControllerByIdentifier(const std::string &identifier);
        /**
         * Unload all view controllers of the scene.
         */
        void unloadAllViewControllers();
        
    protected:
        virtual bool init();
        
        cocos2d::Map<std::string, cocos2d::Ref*> _params;
        cocos2d::Vector<ViewController*> _viewControllers;
    };
}

#endif /* defined(__SCHEME_GAME_SCENE__) */
