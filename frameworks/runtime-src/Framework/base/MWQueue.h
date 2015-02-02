/******************************
 Description: Queue structure.
 Author: M.Wan
 Date: 1/30/2015
 ******************************/

#ifndef __BASE_QUEUE__
#define __BASE_QUEUE__

#include "base/CCRef.h"
#include "FrameworkMacros.h"
#include "ICloneable.h"
#include <list>
#include <string>

MW_FRAMEWORK_BEGIN

/**
 * Linked queue data structure.
 */
class MW_DLL MWQueue : public cocos2d::Ref, public ICloneable<MWQueue>
{
public:
    /**
     * Create a queue structure.
     *
     * @return MWQueue instance which is autoreleased.
     */
    static MWQueue *create();
    
    /**
     * MWQueue constructor.
     */
    MWQueue();
    /**
     * MWQueue destructor.
     */
    virtual ~MWQueue();
    
    /**
     * Insert new value to the queue back.
     *
     * @param val Queue value.
     */
    void enqueue(cocos2d::Ref *val) MW_NOEXCEPTION(MW_WHETHER_THROW_EXCEPTION);
    /**
     * Pop the front of the queue.
     * @note It will return false if the queue is empty.
     *
     * @return Popped result.
     */
    bool dequeue();
    /**
     * Get the front of queue.
     * @note It will return nullptr if the queue is empty.
     *
     * @return The front of the queue.
     */
    cocos2d::Ref *front();
    
    /**
     * Clear all objects.
     */
    void clear();
    
    /**
     * Get the elements count of the queue.
     */
    inline MW_UINT count()
    {
        return _innerQueue.size();
    }
    /**
     * Whether the queue is empty?
     */
    inline bool empty()
    {
        return _innerQueue.empty();
    }
    
    /**
     * ICloneable overrides.
     */
    virtual MWQueue *clone() override;
    
protected:
    std::list<cocos2d::Ref*> _innerQueue;
};

MW_FRAMEWORK_END

#endif /* defined(__BASE_QUEUE__) */
