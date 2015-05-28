/******************************
 Description: Game base scene
 Author: M.Wan
 Date: 1/28/2015
 ******************************/

#ifndef __SCHEME_GAME_SCENE__
#define __SCHEME_GAME_SCENE__

#include "base/CCRef.h"
#include "2d/CCScene.h"
#include "../base/mwbase.h"
#include <map>
#include <string>

MW_FRAMEWORK_BEGIN

class MWViewController;

/**
 * Basic game scene of the framework.
 */
class MW_DLL MWGameScene : public cocos2d::Scene
{
public:
    /**
     * Create a game scene.
     *
     * @return MWGameScene instance which is autoreleased.
     */
    static MWGameScene *create();
    /**
     * Create a game scene with user params.
     *
     * @param params User parameters to pass to the scene.
     *
     * @return MWGameScene instance with params which is autoreleased.
     */
    static MWGameScene *createWithParams(MWDictionary *params);
    
    /**
     * MWGameScene destructor.
     */
    virtual ~MWGameScene();
    
    /**
     * Base class overrides.
     */
    virtual void onEnter() override;
    virtual void onExit() override;
    virtual void onEnterTransitionDidFinish() override;
    virtual void onExitTransitionDidStart() override;
    
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
     * Get the parameter of the specified key, it will throw an exception if the key doesn't exist.
     *
     * @param key Parameter key to consult.
     *
     * @return The parameter value.
     */
    double getNumberParameter(const std::string &key) MW_NOEXCEPTION(MW_WHETHER_THROW_EXCEPTION);
    bool getBooleanParameter(const std::string &key) MW_NOEXCEPTION(MW_WHETHER_THROW_EXCEPTION);
    std::string getStringParameter(const std::string &key) MW_NOEXCEPTION(MW_WHETHER_THROW_EXCEPTION);
    cocos2d::Ref *getRefParameter(const std::string &key) MW_NOEXCEPTION(MW_WHETHER_THROW_EXCEPTION);
    
    /**
     * Segue a view controller from the root view controller with the way of overlapping.
     * @note The behavior is to load a view controller as the child of the root view controller, so when you call this method, you should know what you are doing.
     *
     * @param controller The view controller to load.
     */
    void loadViewController(MWViewController *controller, const std::string &identifier) MW_NOEXCEPTION(MW_WHETHER_THROW_EXCEPTION);
    /**
     * Unload an existed view controller of the scene.
     *
     * @param controller The view controller to unload.
     */
    void unloadViewController(MWViewController *controller) MW_NOEXCEPTION(MW_WHETHER_THROW_EXCEPTION);
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
    /**
     * Get the loaded view controller by the specified identifier.
     *
     * @return The view controller with specified identifier.
     */
    MWViewController *getViewControllerByIdentifier(const std::string &identifier);
    
    MW_SYNTHESIZE(double, _memoryWarningLine, MemoryWarningLine);
    MW_SYNTHESIZE_READONLY(MWDictionary *, _viewControllers, ViewControllers);
    
protected:
    virtual bool init(MWDictionary *params = nullptr);
    
    MWGameScene();
    
    void detectMemory();
    void checkMemory(float dt);
    
    MWDictionary *_params;
};

MW_FRAMEWORK_END

#endif /* defined(__SCHEME_GAME_SCENE__) */
