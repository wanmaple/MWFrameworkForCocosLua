/******************************
 Description: SystemHelper strategy base.
 Author: M.Wan
 Date: 4/10/2015
 ******************************/

#ifndef __PLATFORM_SYSTEMHELPER_STRATEGY__
#define __PLATFORM_SYSTEMHELPER_STRATEGY__

#include "../base/mwbase.h"
#include <string>

MW_FRAMEWORK_BEGIN

class MW_INTERFACE MWSystemHelperStrategy
{
public:
    virtual ~MWSystemHelperStrategy() {}
    
    virtual void copyToPasteBoard(const std::string &content) = 0;
    virtual double getCurrentUsedMemory() = 0;
};

MW_FRAMEWORK_END

#endif
