/******************************
 Description: Linked list structure.
 Author: M.Wan
 Date: 1/30/2015
 ******************************/

#ifndef __BASE_LINKEDLIST__
#define __BASE_LINKEDLIST__

#include "base/CCRef.h"
#include "FrameworkMacros.h"
#include <list>
#include <string>

MW_FRAMEWORK_BEGIN

/**
 * Linked list data structure.
 */
class MW_DLL MWLinkedList : public cocos2d::Ref
{
public:
    /**
     * Create an linkedlist structure.
     *
     * @return MWLinkedList instance which is autoreleased.
     */
    static MWLinkedList *create();
    
    /**
     * MWLinkedList constructor.
     */
    MWLinkedList();
    /**
     * MWLinkedList destructor.
     */
    virtual ~MWLinkedList();
    
    /**
     * Overload methods to append value to the list tail.
     *
     * @param val List value to append.
     */
    void appendObject(double val);
    void appendObject(bool val);
    void appendObject(const std::string &val);
    void appendObject(cocos2d::Ref *val);
    
    /**
     * Clear all objects.
     */
    void clear();
    
    /**
     * Get the elements count of the list.
     */
    MW_UINT count();
    /**
     * Whether the list is empty?
     */
    inline bool empty()
    {
        return this->count() <= 0;
    }
    
protected:
    std::list<cocos2d::Ref*> _innerList;
};

MW_FRAMEWORK_END

#endif /* defined(__BASE_LINKEDLIST__) */
