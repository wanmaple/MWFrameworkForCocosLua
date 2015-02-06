#include "MWGameView.h"
#include <new>

using namespace cocos2d;
using namespace std;

MW_FRAMEWORK_BEGIN

MWGameView *MWGameView::create()
{
    auto pView = new (nothrow) MWGameView();
    if (pView && pView->init()) {
        pView->autorelease();
        return pView;
    }
    CC_SAFE_RELEASE(pView);
    return nullptr;
}

bool MWGameView::init()
{
    return true;
}

MWGameView::MWGameView()
{
    
}

MWGameView::~MWGameView()
{
    
}

void MWGameView::setBackground(cocos2d::Node *bg) MW_NOEXCEPTION(MW_WHETHER_THROW_EXCEPTION)
{
    // check parameter.
    if (!bg) {
        MW_THROW_EXCEPTION(1006);
    }
    CC_SAFE_RELEASE(_bg);
    auto winSize = Director::getInstance()->getWinSize();
    bg->setAnchorPoint(Point(0.5, 0.5));
    bg->setPosition(winSize.width * 0.5, winSize.height * 0.5);
    this->addChild(bg);
    _bg = bg;
}

MW_FRAMEWORK_END