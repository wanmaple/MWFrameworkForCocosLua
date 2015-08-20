/******************************
 Description: UUID generator
 Author: M.Wan
 Date: 4/13/2015
 ******************************/

#ifndef __UTILS_UUIDGENERATOR__
#define __UTILS_UUIDGENERATOR__

#include "../base/mwbase.h"
#include <string>

MW_FRAMEWORK_BEGIN

/**
 * A UUID Generators
 */
class MW_DLL MWUUIDGenerator
{
    /**
     * UUIDGenerator is a singleton.
     */
    MW_SINGLETON(MWUUIDGenerator);
public:
    /**
     * Generate a GUID.
     *
     * @return New GUID.
     */
    std::string generateUUID();
};

MW_FRAMEWORK_END

#endif