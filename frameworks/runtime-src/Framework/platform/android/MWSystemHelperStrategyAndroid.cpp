#if CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID

#include "MWSystemHelperStrategyAndroid.h"

MW_FRAMEWORK_BEGIN

void MWSystemHelperStrategyAndroid::copyToPasteBoard(const std::string &content)
{
}

double MWSystemHelperStrategyAndroid::getCurrentUsedMemory()
{
	return -1;
}

ENetStatus MWSystemHelperStrategyAndroid::checkNetStatus()
{
	return ENetStatus::NO_NETWORK;
}

MW_FRAMEWORK_END

#endif