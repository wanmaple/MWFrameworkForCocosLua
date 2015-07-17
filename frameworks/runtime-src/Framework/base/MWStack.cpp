#include "MWStack.h"
#include "MWException.h"
#include "FrameworkErrors.h"
#include <new>

using namespace cocos2d;
using namespace std;

MW_FRAMEWORK_BEGIN

MWStack *MWStack::create()
{
    auto pStack = new (nothrow) MWStack();
    if (pStack) {
        pStack->autorelease();
        return pStack;
    }
    return nullptr;
}

MWStack::MWStack()
: _innerStack()
{
    
}

MWStack::~MWStack()
{
    this->clear();
}

void MWStack::push(cocos2d::Ref *val)
{
    // check parameter.
    if (!val) {
        MW_THROW_EXCEPTION(1006);
    }
    val->retain();
    _innerStack.push_back(val);
}

bool MWStack::pop()
{
    if (this->empty()) {
        return false;
    }
    Ref *pTop = _innerStack.back();
    _innerStack.pop_back();
    pTop->release();
    return true;
}

cocos2d::Ref *MWStack::top()
{
    if (this->empty()) {
        return nullptr;
    }
    return _innerStack.back();
}

void MWStack::clear()
{
    for (auto &val : _innerStack) {
        val->release();
    }
    _innerStack.clear();
}

MWStack *MWStack::clone()
{
    auto pCopy = new (nothrow) MWStack();
    if (pCopy) {
        for (auto &val : _innerStack) {
            this->push(val);
        }
        pCopy->autorelease();
        return pCopy;
    }
    return nullptr;
}

MW_FRAMEWORK_END