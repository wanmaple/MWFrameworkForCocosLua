/******************************
 Description: View controller base view.
 Author: M.Wan
 Date: 1/30/2015
 ******************************/

#ifndef __SCHEME_GAME_VIEW__
#define __SCHEME_GAME_VIEW__

#include "2d/CCLayer.h"
#include "../base/mwbase.h"

MW_FRAMEWORK_BEGIN

class MWViewController;

/**
 * Basic view of the controller.
 */
class MW_DLL MWGameView : public cocos2d::Layer
{
    friend class MWViewController;
public:
    /**
     * Create a game view.
     *
     * @return MWGameView instance which is autoreleased.
     */
    static MWGameView *create();
    
    /**
     * MWGameView constructor.
     */
    MWGameView();
    /**
     * MWGameView destructor.
     */
    virtual ~MWGameView();
    
    /**
     * Get related controller.
     *
     * @return Related controller of the view.
     */
    inline MWViewController *controller()
    {
        return _controller;
    }
    
protected:
    bool init();
    
    MWViewController *_controller;
};

MW_FRAMEWORK_END

#endif /* defined(__SCHEME_GAME_VIEW__) */
