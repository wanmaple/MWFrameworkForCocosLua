#include "MWNotifier.h"
#include <new>

using namespace cocos2d;
using namespace std;

MW_FRAMEWORK_BEGIN

/** Observer implementation **/
MWObserver *MWObserver::create(cocos2d::Ref *observer, const std::function<void ()> &callback)
{
    auto pOb = new (nothrow) MWObserver();
    if (pOb && pOb->init(observer, callback)) {
        pOb->autorelease();
        return pOb;
    }
    CC_SAFE_RELEASE(pOb);
    return nullptr;
}

MWObserver::~MWObserver()
{
    CC_SAFE_RELEASE(_observer);
}

bool MWObserver::init(cocos2d::Ref *observer, const std::function<void ()> &callback)
{
    if (!observer) {
        return false;
    }
    _observer = observer;
    _observer->retain();
    _callback = callback;
    
    return true;
}

/** Notifier implementation **/

MWNotifier::MWNotifier()
: _observerMap(MWDictionary::create())
{
    _observerMap->retain();
}

MWNotifier::~MWNotifier()
{
    CC_SAFE_RELEASE(_observerMap);
}

void MWNotifier::purge()
{
    delete this;
}

void MWNotifier::addObserver(const std::string &eventName, cocos2d::Ref *observer, const std::function<void ()> &callback)
{
    this->addObserver(eventName, MWObserver::create(observer, callback));
}

void MWNotifier::addObserver(const std::string &eventName, mwframework::MWObserver *observer)
{
    
}

MW_FRAMEWORK_END