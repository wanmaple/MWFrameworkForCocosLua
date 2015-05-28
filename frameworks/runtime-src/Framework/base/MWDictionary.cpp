#include "MWDictionary.h"
#include "MWException.h"
#include "FrameworkErrors.h"
#include "cocos2d.h"
#include <new>

using namespace cocos2d;
using namespace std;

MW_FRAMEWORK_BEGIN

MWDictionary *MWDictionary::create()
{
    auto pDict = new (nothrow) MWDictionary();
    if (pDict) {
        pDict->autorelease();
        return pDict;
    }
    return nullptr;
}

MWDictionary::MWDictionary()
: _innerMap()
{
    
}

MWDictionary::~MWDictionary()
{
    this->clear();
}

std::vector<const std::string> MWDictionary::allKeys()
{
    vector<const std::string> vec;
    
    for (auto iter = _innerMap.cbegin(); iter != _innerMap.cend(); ++iter) {
        vec.push_back(iter->first);
    }
    
    return vec;
}

void MWDictionary::setObjectForKey(const std::string &key, double val)
{
    this->setObjectForKey(key, __Double::create(val));
}

void MWDictionary::setObjectForKey(const std::string &key, bool val)
{
    this->setObjectForKey(key, __Bool::create(val));
}

void MWDictionary::setObjectForKey(const std::string &key, const std::string &val)
{
    this->setObjectForKey(key, __String::create(val));
}

void MWDictionary::setObjectForKey(const std::string &key, cocos2d::Ref *val)
{
    // check parameter.
    if (!val) {
        MW_THROW_EXCEPTION(1006);
    }
    // release the old object if it does exist.
    if (this->hasKey(key)) {
        _innerMap[key]->release();
    }
    val->retain();
    _innerMap[key] = val;
}

double MWDictionary::numberForKey(const std::string &key) MW_NOEXCEPTION(MW_WHETHER_THROW_EXCEPTION)
{
    // check existence.
    if (!this->hasKey(key)) {
        MW_THROW_EXCEPTION(1001);
    }
    __Double *pNum = nullptr;
    if ((pNum = dynamic_cast<__Double*>(_innerMap.at(key)))) {
        return pNum->getValue();
    }
    // wrong type
    MW_THROW_EXCEPTION(1002);
}

bool MWDictionary::booleanForKey(const std::string &key) MW_NOEXCEPTION(MW_WHETHER_THROW_EXCEPTION)
{
    // check existence.
    if (!this->hasKey(key)) {
        MW_THROW_EXCEPTION(1001);
    }
    __Bool *pBool = nullptr;
    if ((pBool = dynamic_cast<__Bool*>(_innerMap.at(key)))) {
        return pBool->getValue();
    }
    // wrong type
    MW_THROW_EXCEPTION(1003);
}

string MWDictionary::stringForKey(const std::string &key) MW_NOEXCEPTION(MW_WHETHER_THROW_EXCEPTION)
{
    // check existence.
    if (!this->hasKey(key)) {
        MW_THROW_EXCEPTION(1001);
    }
    __String *pStr = nullptr;
    if ((pStr = dynamic_cast<__String*>(_innerMap.at(key)))) {
        return pStr->getCString();
    }
    // wrong type
    MW_THROW_EXCEPTION(1004);
}

Ref *MWDictionary::objectForKey(const std::string &key) MW_NOEXCEPTION(MW_WHETHER_THROW_EXCEPTION)
{
    // check existence.
    if (!this->hasKey(key)) {
        MW_THROW_EXCEPTION(1001);
    }
    return _innerMap.at(key);
}

bool MWDictionary::removeObjectForKey(const std::string &key)
{
    // check existence.
    if (!this->hasKey(key)) {
        return false;
    }
    _innerMap[key]->release();
    _innerMap.erase(key);
    return true;
}

void MWDictionary::clear()
{
    for (auto iter = _innerMap.cbegin(); iter != _innerMap.cend(); ++iter) {
        iter->second->release();
    }
    _innerMap.clear();
}

bool MWDictionary::hasKey(const std::string &key)
{
    return _innerMap.find(key) != _innerMap.end();
}

//Ref *MWDictionary::operator[](const std::string &key) MW_NOEXCEPTION(MW_WHETHER_THROW_EXCEPTION)
//{
//    return this->objectForKey(key);
//}

MWDictionary *MWDictionary::clone()
{
    auto pCopy = new (nothrow) MWDictionary();
    if (pCopy) {
        auto keys = this->allKeys();
        for (auto &key : keys) {
            pCopy->setObjectForKey(key, this->objectForKey(key));
        }
        pCopy->autorelease();
        return pCopy;
    }
    return nullptr;
}

MW_FRAMEWORK_END