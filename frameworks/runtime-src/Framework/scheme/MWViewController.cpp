#include "MWViewController.h"
#include "cocos2d.h"
#include "MWGameScene.h"
#include "MWGameLayer.h"
#include "../base/MWException.h"
#include "../base/FrameworkErrors.h"
#include <new>

using namespace cocos2d;
using namespace std;

MW_FRAMEWORK_BEGIN

MWViewController *MWViewController::create(const std::string &identifier)
{
    auto pVc = new (nothrow) MWViewController();
    if (pVc && pVc->initWithIdentifier(identifier)) {
        pVc->autorelease();
        return pVc;
    }
    CC_SAFE_RELEASE(pVc);
    return nullptr;
}

bool MWViewController::initWithIdentifier(const std::string &identifier)
{
    if (identifier.size() <= 0) {
        return false;
    }
    _identifer = identifier;
    return true;
}

MW_FRAMEWORK_END
