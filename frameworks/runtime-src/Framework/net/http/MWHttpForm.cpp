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
    if (_params.size() <= 0) {
        return "";
    }
    std::string paramUrl;
    auto end = --_params.end();
    for (auto iter = _params.begin(); iter != _params.end(); ++iter)
    {
        paramUrl.append(iter->first);
        paramUrl.append("=");
        paramUrl.append(this->urlEncode(iter->second));
        if (iter != end)
        {
            paramUrl.append("&");
        }
    }
    
    return paramUrl;
}

unsigned char MWHttpForm::toHex(unsigned char x)
{
    return  x > 9 ? x + 55 : x + 48;
}

unsigned char MWHttpForm::fromHex(unsigned char x)
{
    unsigned char y;
    if (x >= 'A' && x <= 'Z') y = x - 'A' + 10;
    else if (x >= 'a' && x <= 'z') y = x - 'a' + 10;
    else if (x >= '0' && x <= '9') y = x - '0';
    else assert(0);
    return y;
}

std::string MWHttpForm::urlEncode(const std::string &str)
{
    std::string strTemp = "";
    size_t length = str.length();
    for (size_t i = 0; i < length; i++)
    {
        if (isalnum((unsigned char)str[i]) ||
            (str[i] == '-') ||
            (str[i] == '_') ||
            (str[i] == '.') ||
            (str[i] == '~'))
            strTemp += str[i];
        else if (str[i] == ' ')
            strTemp += "+";
        else
        {
            strTemp += '%';
            strTemp += toHex((unsigned char)str[i] >> 4);
            strTemp += toHex((unsigned char)str[i] % 16);
        }
    }
    return strTemp;
}

std::string MWHttpForm::urlDecode(const std::string &str)
{
    std::string strTemp = "";
    size_t length = str.length();
    for (size_t i = 0; i < length; i++)
    {
        if (str[i] == '+') strTemp += ' ';
        else if (str[i] == '%')
        {
            assert(i + 2 < length);
            unsigned char high = fromHex((unsigned char)str[++i]);
            unsigned char low = fromHex((unsigned char)str[++i]);
            strTemp += high*16 + low;
        }
        else strTemp += str[i];
    }
    return strTemp;
}

MW_FRAMEWORK_END