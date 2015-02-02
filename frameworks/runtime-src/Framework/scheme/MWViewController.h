/******************************
 Description: UI view controller
 Author: M.Wan
 Date: 1/28/2015
 ******************************/

#ifndef __SCHEME_VIEW_CONTROLLER__
#define __SCHEME_VIEW_CONTROLLER__

#include "base/CCRef.h"
#include "../base/mwbase.h"
#include <string>

MW_FRAMEWORK_BEGIN

class IViewControllerDelegate
{
public:
    virtual ~IViewControllerDelegate() {}
    
    /**
     * Notified when the view is already loaded, do some ui initialization here.
     */
    virtual void viewDidLoad() = 0;
    virtual void viewWillAppear() = 0;
    virtual void viewDidAppear() = 0;
    virtual void viewWillDisappear() = 0;
    virtual void viewDidDisappear() = 0;
    virtual void viewDidUnload() = 0;
    virtual void didReceiveMemoryWarning() = 0;
};

class MWGameLayer;
class MWGameScene;

/**
 * Basic view controller of the framework.
 */
class MW_DLL MWViewController : public cocos2d::Ref, public IViewControllerDelegate
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
    inline MWGameLayer *view() const
    {
        return _view;
    }
    
    inline std::string getIdentifier() const
    {
        return _identifer;
    }
    inline void setIdentifier(const std::string &identifier)
    {
        _identifer = identifier;
    }
    
    /**
     * Show a child view.
     *
     * @return Related view of the view controller.
     */
    void segueToViewController(MWViewController *viewController)
    
    /**
     * IViewControllerDelegate overrides
     */
    virtual void viewDidLoad() override;
    virtual void viewWillAppear() override;
    virtual void viewDidAppear() override;
    virtual void viewWillDisappear() override;
    virtual void viewDidDisappear() override;
    virtual void viewDidUnload() override;
    virtual void didReceiveMemoryWarning() override;
    
protected:
    virtual bool initWithIdentifier(const std::string &identifier);
    
    MWGameScene *_scene;
    MWGameLayer *_view;
    std::string _identifer;
};

MW_FRAMEWORK_END

#endif /* defined(__SCHEME_VIEW_CONTROLLER__) */
