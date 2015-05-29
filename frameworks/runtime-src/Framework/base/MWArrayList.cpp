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

void MWArrayList::appendObject(cocos2d::Ref *val)
{
    // check parameter.
    if (!val) {
        MW_THROW_EXCEPTION(1006);
    }
    val->retain();
    _innerVector.push_back(val);
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

cocos2d::Ref *MWArrayList::objectAtIndex(unsigned int index) MW_NOEXCEPTION(MW_WHETHER_THROW_EXCEPTION)
{
    // check if the index is out of range.
    if (index >= _innerVector.size()) {
        MW_THROW_EXCEPTION(1005);
    }
    return _innerVector[index];
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

MW_UINT MWArrayList::lastIndexOfObject(cocos2d::Ref *obj)
{
    for (MW_UINT i = this->count() - 1; (int)i >= 0; --i) {
        if (_innerVector[i] == obj) {
            return i;
        }
    }
    return -1;
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

//Ref *MWArrayList::operator[](int index) MW_NOEXCEPTION(MW_WHETHER_THROW_EXCEPTION)
//{
//    return this->objectAtIndex(index);
//}

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