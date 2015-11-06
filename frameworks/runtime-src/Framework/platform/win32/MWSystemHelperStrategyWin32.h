/******************************
 Description: SystemHelper strategy on win32.
 Author: M.Wan
 Date: 11/6/2015
 ******************************/

#ifndef __PLATFORM_SYSTEMHELPER_STRATEGY_WIN32__
#define __PLATFORM_SYSTEMHELPER_STRATEGY_WIN32__

#include "../../base/mwbase.h"
#include "../MWSystemHelper.h"
#include "../MWSystemHelperStrategy.h"
#include <string>

MW_FRAMEWORK_BEGIN

class MW_DLL MWSystemHelperStrategyWin32 : public MWSystemHelperStrategy
{
public:
    void copyToPasteBoard(const std::string &content) override;
    double getCurrentUsedMemory() override;
    ENetStatus checkNetStatus() override;
};

MW_FRAMEWORK_END

#endif
