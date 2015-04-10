/******************************
 Description: Manipulate some system-related behaviors.
 Author: M.Wan
 Date: 4/10/2015
 ******************************/

#ifndef __PLATFORM_SYSTEMHELPER__
#define __PLATFORM_SYSTEMHELPER__

#include "../base/mwbase.h"
#include <string>

MW_FRAMEWORK_BEGIN

class MWSystemHelperStrategy;

class MW_DLL MWSystemHelper
{
    MW_SINGLETON(MWSystemHelper);
public:
    /**
     * SystemHelper destructor.
     */
    ~MWSystemHelper();
    
    /**
     * Copy the content to the system paste board.
     *
     * @param content The content to copy.
     */
    void copyToPasteBoard(const std::string &content);
    
    /**
     * Get the current memory occupation (MB).
     *
     * @return The memory occupied by the current process.
     */
    double getCurrentUsedMemory();
    
protected:
    MWSystemHelperStrategy *_strategy;
};

MW_FRAMEWORK_END

#endif
