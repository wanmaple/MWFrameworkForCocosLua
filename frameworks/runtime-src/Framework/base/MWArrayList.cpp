#include "MWArrayList.h"
#include "MWException.h"
#include "FrameworkErrors.h"
#include "cocos2d.h"
#include <new>

using namespace cocos2d;
using namespace std;

MW_FRAMEWORK_BEGIN

MWArrayList *MWArrayList::create()
{
    auto pAry = new (nothrow) MWArrayList();
    if (pAry) {
        pAry->autorelease();
        return pAry;
    }
    return nullptr;
}

MWArrayList::MWArrayList()
: _innerVector()
{
    
}

MWArrayList::~MWArrayList()
{
    this->clear();
}

void MWArrayList::appendObject(double val)
{
    this->appendObject(__Double::create(val));
}

void MWArrayList::appendObject(bool val)
{
    this->appendObject(__Bool::create(val));
}

void MWArrayList::appendObject(const std::string &val)
{
    this->appendObject(__String::create(val));
}

void MWArrayList::appendObject(cocos2d::Ref *val)
{
    // check parameter.
    if (!val) {
        MW_THROW_EXCEPTION(1006);
    }
    val->retain();
    _innerVector.push_back(val);
}

void MWArrayList::setObjectAtIndex(double val, unsigned int index) MW_NOEXCEPTION(MW_WHETHER_THROW_EXCEPTION)
{
    this->setObjectAtIndex(__Double::create(val), index);
}

void MWArrayList::setObjectAtIndex(bool val, unsigned int index) MW_NOEXCEPTION(MW_WHETHER_THROW_EXCEPTION)
{
    this->setObjectAtIndex(__Bool::create(val), index);
}

void MWArrayList::setObjectAtIndex(const std::string &val, unsigned int index) MW_NOEXCEPTION(MW_WHETHER_THROW_EXCEPTION)
{
    this->setObjectAtIndex(__String::create(val), index);
}

void MWArrayList::setObjectAtIndex(cocos2d::Ref *val, unsigned int index) MW_NOEXCEPTION(MW_WHETHER_THROW_EXCEPTION)
{
    // check if the index is out of range.
    if (index >= _innerVector.size()) {
        MW_THROW_EXCEPTION(1005);
    }
    _innerVector[index]->release();
    val->retain();
    _innerVector[index] = val;
}

void MWArrayList::insertObjectAtIndex(double val, unsigned int index) MW_NOEXCEPTION(MW_WHETHER_THROW_EXCEPTION)
{
    this->insertObjectAtIndex(__Double::create(val), index);
}

void MWArrayList::insertObjectAtIndex(bool val, unsigned int index) MW_NOEXCEPTION(MW_WHETHER_THROW_EXCEPTION)
{
    this->insertObjectAtIndex(__Bool::create(val), index);
}

void MWArrayList::insertObjectAtIndex(const std::string &val, unsigned int index) MW_NOEXCEPTION(MW_WHETHER_THROW_EXCEPTION)
{
    this->insertObjectAtIndex(__String::create(val), index);
}

void MWArrayList::insertObjectAtIndex(cocos2d::Ref *val, unsigned int index) MW_NOEXCEPTION(MW_WHETHER_THROW_EXCEPTION)
{
    // check parameter.
    if (!val) {
        MW_THROW_EXCEPTION(1006);
    }
    // check if the index is out of range.
    if (index >= _innerVector.size()) {
        MW_THROW_EXCEPTION(1005);
    }
    val->retain();
    _innerVector.insert(_innerVector.begin() + index, val);
}

double MWArrayList::numberAtIndex(unsigned int index) MW_NOEXCEPTION(MW_WHETHER_THROW_EXCEPTION)
{
    // check if the index is out of range.
    if (index >= _innerVector.size()) {
        MW_THROW_EXCEPTION(1005);
    }
    __Double *pNum = nullptr;
    if ((pNum = dynamic_cast<__Double*>(_innerVector[index]))) {
        return pNum->getValue();
    }
    // wrong type
    MW_THROW_EXCEPTION(1007);
}

bool MWArrayList::booleanAtIndex(unsigned int index) MW_NOEXCEPTION(MW_WHETHER_THROW_EXCEPTION)
{
    // check if the index is out of range.
    if (index >= _innerVector.size()) {
        MW_THROW_EXCEPTION(1005);
    }
    __Bool *pBool = nullptr;
    if ((pBool = dynamic_cast<__Bool*>(_innerVector[index]))) {
        return pBool->getValue();
    }
    // wrong type
    MW_THROW_EXCEPTION(1008);
}

std::string MWArrayList::stringAtIndex(unsigned int index) MW_NOEXCEPTION(MW_WHETHER_THROW_EXCEPTION)
{
    // check if the index is out of range.
    if (index >= _innerVector.size()) {
        MW_THROW_EXCEPTION(1005);
    }
    __String *pStr = nullptr;
    if ((pStr = dynamic_cast<__String*>(_innerVector[index]))) {
        return pStr->getCString();
    }
    // wrong type
    MW_THROW_EXCEPTION(1009);
}

cocos2d::Ref *MWArrayList::objectAtIndex(unsigned int index) MW_NOEXCEPTION(MW_WHETHER_THROW_EXCEPTION)
{
    // check if the index is out of range.
    if (index >= _innerVector.size()) {
        MW_THROW_EXCEPTION(1005);
    }
    return _innerVector[index];
}

MW_UINT MWArrayList::indexOfObject(double obj)
{
    __Double *pNum = nullptr;
    for (MW_UINT i = 0; i < this->count(); ++i) {
        pNum = dynamic_cast<__Double*>(_innerVector[i]);
        if (pNum && pNum->getValue() == obj) {
            return i;
        }
    }
    return -1;
}

MW_UINT MWArrayList::indexOfObject(bool obj)
{
    __Bool *pBool = nullptr;
    for (MW_UINT i = 0; i < this->count(); ++i) {
        pBool = dynamic_cast<__Bool*>(_innerVector[i]);
        if (pBool && pBool->getValue() == obj) {
            return i;
        }
    }
    return -1;
}

MW_UINT MWArrayList::indexOfObject(const std::string &obj)
{
    __String *pStr = nullptr;
    for (MW_UINT i = 0; i < this->count(); ++i) {
        pStr = dynamic_cast<__String*>(_innerVector[i]);
        if (pStr && string(pStr->getCString()) == obj) {
            return i;
        }
    }
    return -1;
}

MW_UINT MWArrayList::indexOfObject(cocos2d::Ref *obj)
{
    for (MW_UINT i = 0; i < this->count(); ++i) {
        if (_innerVector[i] == obj) {
            return i;
        }
    }
    return -1;
}

MW_UINT MWArrayList::lastIndexOfObject(double obj)
{
    __Double *pNum = nullptr;
    // Be aware of reverse order of unsigned types.
    for (MW_UINT i = this->count() - 1; (int)i >= 0; --i) {
        pNum = dynamic_cast<__Double*>(_innerVector[i]);
        if (pNum && pNum->getValue() == obj) {
            return i;
        }
    }
    return -1;
}

bool MWArrayList::removeObject(double obj)
{
    __Double *pNum = nullptr;
    for (MW_UINT i = 0; i < this->count(); ++i) {
        pNum = dynamic_cast<__Double*>(_innerVector[i]);
        if (pNum && pNum->getValue() == obj) {
            this->removeObjectAtIndex(i);
            return true;
        }
    }
    return false;
}

bool MWArrayList::removeObject(bool obj)
{
    __Bool *pBool = nullptr;
    for (MW_UINT i = 0; i < this->count(); ++i) {
        pBool = dynamic_cast<__Bool*>(_innerVector[i]);
        if (pBool && pBool->getValue() == obj) {
            this->removeObjectAtIndex(i);
            return true;
        }
    }
    return false;
}

bool MWArrayList::removeObject(const std::string &obj)
{
    __String *pStr = nullptr;
    for (MW_UINT i = 0; i < this->count(); ++i) {
        pStr = dynamic_cast<__String*>(_innerVector[i]);
        if (pStr && string(pStr->getCString()) == obj) {
            this->removeObjectAtIndex(i);
            return true;
        }
    }
    return false;
}

bool MWArrayList::removeObject(cocos2d::Ref *obj)
{
    for (MW_UINT i = 0; i < this->count(); ++i) {
        if (_innerVector[i] == obj) {
            this->removeObjectAtIndex(i);
            return true;
        }
    }
    return false;
}

bool MWArrayList::removeObjectAtIndex(unsigned int index) MW_NOEXCEPTION(MW_WHETHER_THROW_EXCEPTION)
{
    // check if the index is out of range.
    if (index >= _innerVector.size()) {
        return false;
    }
    _innerVector[index]->release();
    _innerVector.erase(_innerVector.begin() + index);
    return true;
}

void MWArrayList::clear()
{
    for (auto iter = _innerVector.cbegin(); iter != _innerVector.cend(); ++iter) {
        (*iter)->release();
    }
    _innerVector.clear();
}

Ref *MWArrayList::operator[](int index) MW_NOEXCEPTION(MW_WHETHER_THROW_EXCEPTION)
{
    return this->objectAtIndex(index);
}

MWArrayList *MWArrayList::clone()
{
    auto pCopy = new (nothrow) MWArrayList();
    if (pCopy) {
        for (auto &val : _innerVector) {
            pCopy->appendObject(val);
        }
        pCopy->autorelease();
        return pCopy;
    }
    return nullptr;
}

MW_FRAMEWORK_END