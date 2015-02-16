#include "MWJsonElement.h"
#include "cocos2d.h"
#include <new>

using namespace cocos2d;
using namespace std;

MW_FRAMEWORK_BEGIN

MWJsonBoolean *MWJsonBoolean::create(bool value)
{
    auto pElement = new (nothrow) MWJsonBoolean(value);
    if (pElement) {
        pElement->autorelease();
        return pElement;
    }
    return nullptr;
}

MWJsonBoolean::MWJsonBoolean(bool value)
: _val(value)
{
}

bool MWJsonBoolean::boolValue()
{
    return _val;
}

double MWJsonBoolean::numberValue()
{
    if (_val) {
        return 1;
    } else {
        return 0;
    }
}

const char *MWJsonBoolean::stringValue()
{
    if (_val) {
        return "true";
    } else {
        return "false";
    }
}

MWJsonNumber *MWJsonNumber::create(double value)
{
    auto pElement = new (nothrow) MWJsonNumber(value);
    if (pElement) {
        pElement->autorelease();
        return pElement;
    }
    return nullptr;
}


MWJsonNumber::MWJsonNumber(double value)
: _val(value)
{
}

bool MWJsonNumber::boolValue()
{
    return bool(_val);
}

double MWJsonNumber::numberValue()
{
    return _val;
}

const char *MWJsonNumber::stringValue()
{
    __String *pStr = __String::createWithFormat("%lf", _val);
    // format the number.
    std::string str = pStr->getCString();
    while (str.find_first_of('.') != -1 && (str.at(str.size() - 1) == '.' || str.at(str.size() - 1) == '0')) {
        str.erase(str.begin() + str.size() - 1);
    }
    return str.c_str();
}

MWJsonString *MWJsonString::create(const string &value)
{
    auto pElement = new (nothrow) MWJsonString(value);
    if (pElement) {
        pElement->autorelease();
        return pElement;
    }
    return nullptr;
}


MWJsonString::MWJsonString(const std::string &value)
: _val(value)
{
}

bool MWJsonString::boolValue()
{
    if (_val.size() > 0) {
        return true;
    } else {
        return false;
    }
}

double MWJsonString::numberValue()
{
    double num;
    sscanf(_val.c_str(), "%lf", &num);
    return num;
}

const char *MWJsonString::stringValue()
{
    return _val.c_str();
}

MW_FRAMEWORK_END