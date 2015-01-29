/******************************
 Description: Make the object uncopyable, just inherit this class privately
 Author: M.Wan
 Date: 1/28/2015
 ******************************/

#ifndef __BASE_UNCOPYABLE__
#define __BASE_UNCOPYABLE__

#include "FrameworkMacros.h"

MW_FRAMEWORK_BEGIN

/**
 * Make object uncopyable.
 */
class IUncopyable
{
protected:
    IUncopyable() {}
    
private:
    IUncopyable(const IUncopyable&);
    IUncopyable &operator=(const IUncopyable&);
};

MW_FRAMEWORK_END

#endif
