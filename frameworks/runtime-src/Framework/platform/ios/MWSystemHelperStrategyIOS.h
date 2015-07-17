/******************************
 Description: SystemHelper strategy on iOS.
 Author: M.Wan
 Date: 4/10/2015
 ******************************/

#ifndef __PLATFORM_SYSTEMHELPER_STRATEGY_IOS__
#define __PLATFORM_SYSTEMHELPER_STRATEGY_IOS__

#include "../../base/mwbase.h"
#include "../MWSystemHelper.h"
#include "../MWSystemHelperStrategy.h"
#include <string>

MW_FRAMEWORK_BEGIN

class MW_DLL MWSystemHelperStrategyIos : public MWSystemHelperStrategy
{
public:
    void copyToPasteBoard(const std::string &content) override;
    double getCurrentUsedMemory() override;
    ENetStatus checkNetStatus() override;
};

MW_FRAMEWORK_END

#endif
