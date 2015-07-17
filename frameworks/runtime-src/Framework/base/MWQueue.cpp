#include "MWQueue.h"
#include "MWException.h"
#include "FrameworkErrors.h"
#include <new>

using namespace cocos2d;
using namespace std;

MW_FRAMEWORK_BEGIN

MWQueue *MWQueue::create()
{
    auto pQueue = new (nothrow) MWQueue();
    if (pQueue) {
        pQueue->autorelease();
        return pQueue;
    }
    return nullptr;
}

MWQueue::MWQueue()
: _innerQueue()
{
    
}

MWQueue::~MWQueue()
{
    this->clear();
}

void MWQueue::enqueue(cocos2d::Ref *val)
{
    // check parameter.
    if (!val) {
        MW_THROW_EXCEPTION(1006);
    }
    val->retain();
    _innerQueue.push_back(val);
}

bool MWQueue::dequeue()
{
    if (this->empty()) {
        return false;
    }
    Ref *pFront = _innerQueue.front();
    _innerQueue.pop_front();
    pFront->release();
    return true;
}

cocos2d::Ref *MWQueue::front()
{
    if (this->empty()) {
        return nullptr;
    }
    return _innerQueue.front();
}

void MWQueue::clear()
{
    for (auto &val : _innerQueue) {
        val->release();
    }
    _innerQueue.clear();
}

MWQueue *MWQueue::clone()
{
    auto pCopy = new (nothrow) MWQueue();
    if (pCopy) {
        for (auto &val : _innerQueue) {
            pCopy->enqueue(val);
        }
        pCopy->autorelease();
        return pCopy;
    }
    return nullptr;
}

MW_FRAMEWORK_END