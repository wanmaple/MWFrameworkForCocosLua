#include "MWGifFrame.h"

#include <new>

using namespace cocos2d;
using namespace std;

MW_FRAMEWORK_BEGIN

MWGifFrame *MWGifFrame::create(SpriteFrame *spriteFrame, MW_UINT duration)
{
    auto pRet = new (nothrow) MWGifFrame();
    if (pRet && pRet->init(spriteFrame, duration)) {
        pRet->autorelease();
        return pRet;
    }
    CC_SAFE_RELEASE(pRet);
    return nullptr;
}

bool MWGifFrame::init(SpriteFrame *spriteFrame, MW_UINT duration)
{
    if (!spriteFrame) {
        return false;
    }
    _spriteFrame = spriteFrame;
    CC_SAFE_RETAIN(_spriteFrame);
    _duration = duration;
    
    return true;
}

MWGifFrame::MWGifFrame()
: _spriteFrame(nullptr)
, _duration(0)
{
    
}

MWGifFrame::~MWGifFrame()
{
    CC_SAFE_RELEASE(_spriteFrame);
}

void MWGifFrame::setSpriteFrame(cocos2d::SpriteFrame *spriteFrame)
{
    if (!spriteFrame) {
        MW_THROW_EXCEPTION(1006);
    }
    CC_SAFE_RELEASE(_spriteFrame);
    _spriteFrame = spriteFrame;
    CC_SAFE_RETAIN(_spriteFrame);
}

MW_FRAMEWORK_END