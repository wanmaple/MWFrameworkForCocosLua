/******************************
 Description: The interface of serializing object.
 Author: M.Wan
 Date: 2/5/2015
 ******************************/

#ifndef __BASE_SERIALIZABLE__
#define __BASE_SERIALIZABLE__

#include "FrameworkMacros.h"

MW_FRAMEWORK_BEGIN

/**
 * Enable to serialize the object.
 */
class ISerializable
{
public:
    virtual ~ISerializable() {}
    
    virtual void *serialize() = 0;
};

MW_FRAMEWORK_END

#endif
