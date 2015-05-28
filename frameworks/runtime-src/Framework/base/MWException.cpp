#include "MWException.h"
#include "cocos2d.h"
#include <new>

using namespace cocos2d;
using namespace std;

MW_FRAMEWORK_BEGIN

MWException *MWException::create(int errCode, const char *msg)
{
    auto pEx = new (nothrow) MWException(errCode, msg);
    if (pEx) {
        pEx->autorelease();
        return pEx;
    }
    return nullptr;
}

MWException::MWException(int errCode, const char *msg)
: _errorCode(errCode)
, _errorMsg(msg)
{
    
}

const char *MWException::what() const
{
    char buffer[1024];
    sprintf(buffer, "Error message: %s\tError code: %d", _errorMsg.c_str(), _errorCode);
    string msg = buffer;
    return msg.c_str();
}

MW_FRAMEWORK_END