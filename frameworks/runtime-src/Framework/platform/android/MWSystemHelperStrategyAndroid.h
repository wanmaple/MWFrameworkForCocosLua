/******************************
 Description: SystemHelper strategy on Android.
 Author: M.Wan
 Date: 8/18/2015
 ******************************/

#ifndef __PLATFORM_SYSTEMHELPER_STRATEGY_ANDROID__
#define __PLATFORM_SYSTEMHELPER_STRATEGY_ANDROID__

#include "../../base/mwbase.h"
#include "../MWSystemHelper.h"
#include "../MWSystemHelperStrategy.h"
#include <string>

MW_FRAMEWORK_BEGIN

class MW_DLL MWSystemHelperStrategyAndroid : public MWSystemHelperStrategy
{
public:
    void copyToPasteBoard(const std::string &content) override;
    double getCurrentUsedMemory() override;
    ENetStatus checkNetStatus() override;
};

MW_FRAMEWORK_END

#endif
