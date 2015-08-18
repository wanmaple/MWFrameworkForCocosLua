#include "MWSystemHelper.h"

#include "cocos2d.h"
#if CC_TARGET_PLATFORM == CC_PLATFORM_IOS
#include "ios/MWSystemHelperStrategyIOS.h"
#elif CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID
#include "android/MWSystemHelperStrategyAndroid.h"
#endif

MW_FRAMEWORK_BEGIN

MWSystemHelper::MWSystemHelper()
#if CC_TARGET_PLATFORM == CC_PLATFORM_IOS
: _strategy(new MWSystemHelperStrategyIos())
#elif CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID
: _strategy(new MWSystemHelperStrategyAndroid())
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

ENetStatus MWSystemHelper::checkNetStatus()
{
    if (_strategy) {
        return _strategy->checkNetStatus();
    }
    MW_THROW_EXCEPTION(1012);
}

void MWSystemHelper::copyToPasteBoard(const std::string &content)
{
    if (_strategy) {
        _strategy->copyToPasteBoard(content);
    }
    MW_THROW_EXCEPTION(1012);
}

double MWSystemHelper::getCurrentUsedMemory()
{
    if (_strategy) {
        return _strategy->getCurrentUsedMemory();
    }
    MW_THROW_EXCEPTION(1012);
}

MW_FRAMEWORK_END