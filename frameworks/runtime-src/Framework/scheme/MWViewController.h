/******************************
 Description: UI view controller
 Author: M.Wan
 Date: 1/28/2015
 ******************************/

#ifndef __SCHEME_VIEW_CONTROLLER__
#define __SCHEME_VIEW_CONTROLLER__

#include "cocos2d.h"
#include "../base/mwbase.h"
#include <string>

MW_FRAMEWORK_BEGIN

class MW_INTERFACE IViewControllerDelegate
{
public:
    virtual ~IViewControllerDelegate() {}
    
    /**
     * Notified when the view is already loaded, do some ui initialization here.
     */
    virtual void viewDidLoad() = 0;
    virtual void viewDidUnload() = 0;
    virtual void didReceiveMemoryWarning() = 0;
};

class MWGameView;
class MWGameScene;

/**
 * Basic view controller of the framework.
 */
class MW_DLL MWViewController : public MWObject, public IViewControllerDelegate
{
    friend class MWGameScene;
public:
    /**
     * Create a view controller.
     *
     * @param identifier View controller identifier maintained by the scene.
     *
     * @return MWViewController instance which is autoreleased.
     */
    static MWViewController *create(const std::string &identifier = "");
    
    /**
     * MWViewController constructor.
     */
    MWViewController();
    /**
     * MWViewController destructor.
     */
    virtual ~MWViewController();
    
    /**
     * Get admin scene.
     *
     * @return Admin scene of the view controller.
     */
    inline MWGameScene *scene() const
    {
        return _scene;
    }
    /**
     * Get related view.
     *
     * @return Related view of the view controller.
     */
    inline MWGameView *view() const
    {
        return _view;
    }
    
    /**
     * Identifier getter and setter.
     */
    inline std::string getIdentifier() const
    {
        return _identifer;
    }
    inline void setIdentifier(const std::string &identifier)
    {
        _identifer = identifier;
    }
    
    /**
     * IViewControllerDelegate overrides
     */
    virtual void viewDidLoad() override;
    virtual void viewDidUnload() override;
    virtual void didReceiveMemoryWarning() override;
    
protected:
    virtual bool initWithIdentifier(const std::string &identifier);
    
    MWGameScene *_scene;
    MWGameView *_view;
    std::string _identifer;
};

MW_FRAMEWORK_END

#endif /* defined(__SCHEME_VIEW_CONTROLLER__) */
