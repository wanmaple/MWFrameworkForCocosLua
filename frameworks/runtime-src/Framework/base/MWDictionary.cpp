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

std::vector<std::string> MWDictionary::allKeys()
{
    vector<std::string> vec;
    
    for (auto iter = _innerMap.cbegin(); iter != _innerMap.cend(); ++iter) {
        vec.push_back(iter->first);
    }
    
    return vec;
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

Ref *MWDictionary::objectForKey(const std::string &key)
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

//Ref *MWDictionary::operator[](const std::string &key)
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