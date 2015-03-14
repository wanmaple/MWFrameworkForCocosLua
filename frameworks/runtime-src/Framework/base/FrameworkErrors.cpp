#include "FrameworkErrors.h"
#include <unordered_map>

MW_FRAMEWORK_BEGIN

static std::unordered_map<int, const char*> g_errorMap = {
    // basic errors, 1001 - 2000.
    { 1001, "The dictionary key doesn't exist." },
    { 1002, "The dictionary mapped value of the key is not a number value." },
    { 1003, "The dictionary mapped value of the key is not a boolean value." },
    { 1004, "The dictionary mapped value of the key is not a string value." },
    { 1005, "The index is out of range." },
    { 1006, "Argument can't be null or empty." },
    { 1007, "The list value of the index is not a number value." },
    { 1008, "The list value of the index is not a boolean value." },
    { 1009, "The list value of the index is not a string value." },
    { 1010, "Invalid object." },
    // io errors, 2001 - 3000.
    { 2001, "The file doesn't exist." },
    // network errors, 5001 - 6000.
    { 5002, "Unknown or unregisted network service." },
    { 5002, "Unknown or unregisted network protocol." },
    { 5003, "Duplicated network service." },
};

const char *GetErrorString(int errCode)
{
    return g_errorMap[errCode];
}

MW_FRAMEWORK_END
