/******************************
 Description: Framework error info.
 Author: M.Wan
 Date: 1/29/2015
 ******************************/

#ifndef __FRAMEWORK_ERRORS__
#define __FRAMEWORK_ERRORS__

#include "FrameworkMacros.h"
#include <unordered_map>

static std::unordered_map<int, const char*> g_errorMap = {
    { 1001, "The dictionary key doesn't exist." },
    { 1002, "The dictionary mapped value of the key is not a number value." },
    { 1003, "The dictionary mapped value of the key is not a boolean value." },
    { 1004, "The dictionary mapped value of the key is not a string value." },
};

MW_FRAMEWORK_BEGIN

const char *GetErrorString(int errCode)
{
    return g_errorMap[errCode];
}

MW_FRAMEWORK_END

#endif
