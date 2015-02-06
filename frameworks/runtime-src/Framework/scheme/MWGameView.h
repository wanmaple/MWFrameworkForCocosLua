/******************************
 Description: View controller base view.
 Author: M.Wan
 Date: 1/30/2015
 ******************************/

#ifndef __SCHEME_GAME_VIEW__
#define __SCHEME_GAME_VIEW__

#include "2d/CCNode.h"
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
     * Set the background image of the view.
     *
     * @param bg Background node to display.
     */
    void setBackground(cocos2d::Node *bg) MW_NOEXCEPTION(MW_WHETHER_THROW_EXCEPTION);
    
protected:
    bool init();
    
    cocos2d::Node *_bg;
};

MW_FRAMEWORK_END

#endif /* defined(__SCHEME_GAME_VIEW__) */
