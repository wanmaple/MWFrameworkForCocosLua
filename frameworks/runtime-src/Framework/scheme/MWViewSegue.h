/******************************
 Description: Segue provides a way how to initialize the game view when loading a view controller.
 Author: M.Wan
 Date: 4/13/2015
 ******************************/

#ifndef __SCHEME_VIEW_SEGUE__
#define __SCHEME_VIEW_SEGUE__

#include "../base/mwbase.h"

MW_FRAMEWORK_BEGIN

class MWGameView;
class MWGameScene;

class MW_INTERFACE MWViewSegueDelegate
{
public:
    virtual ~MWViewSegueDelegate() {}
    
    /**
     * Define how to initialize the view before loading a view controller.
     */
    virtual void viewReadyToSegue(MWGameView *view) = 0;
    /**
     * What to do after loading a view controller.
     */
    virtual void viewDidSegue(MWGameScene *scene) = 0;
    /**
     * What to do after unloading a view controller.
     */
    virtual void viewDidSegueBack(MWGameScene *scene) = 0;
};

/**
 * Basic view segue.
 */
class MW_DLL MWViewSegue : public MWObject, public MWViewSegueDelegate
{
public:
    /**
     * Create a view segue.
     *
     * @return MWViewSegue instance which is autoreleased.
     */
    static MWViewSegue *create();
    
    virtual void viewReadyToSegue(MWGameView *view) override;
    virtual void viewDidSegue(MWGameScene *scene) override;
    virtual void viewDidSegueBack(MWGameScene *scene) override;
    
protected:
    bool init();
};

MW_FRAMEWORK_END

#endif
