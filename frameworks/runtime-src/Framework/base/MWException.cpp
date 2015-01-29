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
    CC_SAFE_RELEASE(pEx);
    return nullptr;
}

MWException::MWException(int errCode, const char *msg)
: _errorCode(errCode)
, _errorMsg(msg)
{
    
}

const char *MWException::what() const _NOEXCEPT
{
    return _errorMsg.c_str();
}

MW_FRAMEWORK_END