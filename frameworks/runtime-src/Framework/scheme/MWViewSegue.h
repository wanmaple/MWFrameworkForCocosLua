/******************************
 Description: Segue provides a way how to initialize the game view when loading a view controller.
 Author: M.Wan
 Date: 4/13/2015
 ******************************/

#ifndef __SCHEME_VIEW_SEGUE__
#define __SCHEME_VIEW_SEGUE__

#include "../base/mwbase.h"

MW_FRAMEWORK_BEGIN

class MWViewController;

class MW_INTERFACE MWViewSegueDelegate
{
public:
    virtual ~MWViewSegueDelegate() {}
    
    /**
     * Define how to initialize the view before loading a view controller.
     */
    virtual void viewReadyToSegue(MWViewController *controller) = 0;
    /**
     * What to do after loading a view controller.
     */
    virtual void viewDidSegue(MWViewController *controller) = 0;
    /**
     * What to do after unloading a view controller.
     */
    virtual void viewDidSegueBack(MWViewController *controller) = 0;
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
    
    virtual void viewReadyToSegue(MWViewController *controller) override;
    virtual void viewDidSegue(MWViewController *controller) override;
    virtual void viewDidSegueBack(MWViewController *controller) override;
    
protected:
    bool init();
};

MW_FRAMEWORK_END

#endif
