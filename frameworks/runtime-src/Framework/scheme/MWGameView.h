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
     * For screen fit solutions, it will drag the top-left content to the top-left corner, top-right content to the top-right corner, bottom-left content to the bottom-left corner, and bottom-right content to the bottom-right corner.
     *
     * @param content The content to display.
     * @param zOrder Z-axis value.
     */
    void addToTopLeft(cocos2d::Node *content, int zOrder);
    void addToTopRight(cocos2d::Node *content, int zOrder);
    void addToBottomLeft(cocos2d::Node *content, int zOrder);
    void addToBottomRight(cocos2d::Node *content, int zOrder);
    
    /**
     * Set the background image of the view.
     *
     * @param bg Background node to display.
     */
    void setBackground(cocos2d::Node *bg);
    
    virtual void sortAllChildren() override;
    
protected:
    bool init();
    
    cocos2d::Node *_bg;
    cocos2d::Layer *_topLeftCornor;
    cocos2d::Layer *_topRightCornor;
    cocos2d::Layer *_bottomLeftCornor;
    cocos2d::Layer *_bottomRightCornor;
};

MW_FRAMEWORK_END

#endif /* defined(__SCHEME_GAME_VIEW__) */
