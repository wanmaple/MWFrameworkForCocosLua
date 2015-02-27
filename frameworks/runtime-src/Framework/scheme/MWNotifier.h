/******************************
 Description: Notifier of observer pattern.
 Author: M.Wan
 Date: 2/27/2015
 ******************************/

#ifndef __SCHEME_NOTIFIER__
#define __SCHEME_NOTIFIER__

#include "base/CCRef.h"
#include "../base/mwbase.h"
#include <string>
#include <functional>

MW_FRAMEWORK_BEGIN

/**
 * Observer.
 */
class MW_DLL MWObserver : public MWObject
{
public:
    /**
     * Create an observer.
     *
     * @param observer Subscriber object.
     * @param callback The callback function when the sender publish the information.
     *
     * @return MWObserver instance which is autoreleased.
     */
    static MWObserver *create(cocos2d::Ref *observer, const std::function<void()> &callback);
    
    /**
     * Observer destructor.
     */
    virtual ~MWObserver();
    
protected:
    bool init(cocos2d::Ref *observer, const std::function<void()> &callback);
    
    cocos2d::Ref *_observer;
    std::function<void()> _callback;
};

/**
 * Observer notifier.
 */
class MW_DLL MWNotifier
{
    MW_SINGLETON(MWNotifier)
public:
    ~MWNotifier();
    
    /**
     * Clean the singleton.
     */
    void purge();
    
    /**
     * Add an observer of the specified event.
     *
     * @eventName Event name.
     * @param observer Subscriber to add.
     * @param callback The callback function when the sender publish the information.
     */
    void addObserver(const std::string &eventName, cocos2d::Ref *observer, const std::function<void()> &callback);
    /**
     * Add an observer of the specified event.
     *
     * @eventName Event name.
     * @param observer Encapsulated MWObserver object.
     * @param callback The callback function when the sender publish the information.
     */
    void addObserver(const std::string &eventName, MWObserver *observer);
    /**
     * Remove the specified observer of the specified event.
     *
     * @eventName Event name.
     * @param observer Subscriber to remove.
     */
    void removeObserver(const std::string &eventName, cocos2d::Ref *observer);
    /**
     * Add all observers of the specified event.
     *
     * @eventName Event name.
     */
    void removeAllObservers(const std::string &eventName);
    /**
     * Send a notification of the event.
     *
     * @eventName Event name.
     */
    void notify(const std::string &eventName, ...);
    
protected:
    MWDictionary *_observerMap;
};

MW_FRAMEWORK_END

#endif /* defined(__SCHEME_NOTIFIER__) */
