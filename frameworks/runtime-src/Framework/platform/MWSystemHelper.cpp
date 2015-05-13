#include "MWSystemHelper.h"

#include "cocos2d.h"
#if CC_TARGET_PLATFORM == CC_PLATFORM_IOS
#include "MWSystemHelperStrategyIOS.h"
#endif

MW_FRAMEWORK_BEGIN

MWSystemHelper::MWSystemHelper()
#if CC_TARGET_PLATFORM == CC_PLATFORM_IOS
: _strategy(new MWSystemHelperStrategyIos())
#endif
{
}

MWSystemHelper::~MWSystemHelper()
{
    CC_SAFE_DELETE(_strategy);
}

MW_ULONG MWSystemHelper::millisecondsNow()
{
    timeval now;
    gettimeofday(&now, nullptr);
    return now.tv_sec * 1000 + now.tv_usec / 1000;
}

void MWSystemHelper::copyToPasteBoard(const std::string &content)
{
    if (_strategy) {
        _strategy->copyToPasteBoard(content);
    }
    CCLOG("Unimplemented platform.");
}

double MWSystemHelper::getCurrentUsedMemory()
{
    if (_strategy) {
        return _strategy->getCurrentUsedMemory();
    }
    CCLOG("Unimplemented platform.");
    return -1;
}

MW_FRAMEWORK_END