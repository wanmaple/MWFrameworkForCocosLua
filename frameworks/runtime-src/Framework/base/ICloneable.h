/******************************
 Description: The interface of cloning object.
 Author: M.Wan
 Date: 1/30/2015
 ******************************/

#ifndef __BASE_CLONEABLE__
#define __BASE_CLONEABLE__

#include "FrameworkMacros.h"

MW_FRAMEWORK_BEGIN

/**
 * Enable to clone the object.
 */
template<typename T>
class ICloneable
{
public:
    virtual ~ICloneable() {}
    virtual T *clone() = 0;
};

MW_FRAMEWORK_END

#endif
