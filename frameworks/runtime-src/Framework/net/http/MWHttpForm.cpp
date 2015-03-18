#include "MWHttpForm.h"

#include <new>

using namespace std;

MW_FRAMEWORK_BEGIN

MWHttpForm *MWHttpForm::create()
{
    auto pRet = new (nothrow) MWHttpForm();
    if (pRet && pRet->_init()) {
        pRet->autorelease();
        return pRet;
    }
    CC_SAFE_RELEASE(pRet);
    return nullptr;
}

bool MWHttpForm::_init()
{
    return true;
}

MWHttpForm::~MWHttpForm()
{
}

void MWHttpForm::putParam(const std::string &paramName, const std::string &paramValue) MW_NOEXCEPTION(MW_WHETHER_THROW_EXCEPTION)
{
    if (paramName.size() <= 0) {
        MW_THROW_EXCEPTION(1006);
    }
    
    _params[paramName] = paramValue;
}

const char *MWHttpForm::getParam(const std::string &paramName)
{
    if (_params.find(paramName) != _params.end())
    {
        return _params[paramName].c_str();
    }
    return nullptr;
}

void MWHttpForm::removeParam(const std::string &paramName) MW_NOEXCEPTION(MW_WHETHER_THROW_EXCEPTION)
{
    if (paramName.size() <= 0) {
        MW_THROW_EXCEPTION(1006);
    }
    
    auto iter = _params.find(paramName);
    if (iter != _params.end())
    {
        _params.erase(iter);
    }
}

std::string MWHttpForm::toString()
{
    std::string paramUrl;
    auto end = --_params.end();
    for (auto iter = _params.begin(); iter != _params.end(); ++iter)
    {
        paramUrl.append(iter->first);
        paramUrl.append("=");
        paramUrl.append(iter->second);
        if (iter != end)
        {
            paramUrl.append("&");
        }
    }
    
    return paramUrl;
}

MW_FRAMEWORK_END