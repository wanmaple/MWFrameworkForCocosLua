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
: _controller(nullptr)
{
    
}

MWGameView::~MWGameView()
{
    
}

MW_FRAMEWORK_END