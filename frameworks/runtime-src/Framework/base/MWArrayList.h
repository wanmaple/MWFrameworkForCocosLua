/******************************
 Description: Dictionary structure.
 Author: M.Wan
 Date: 1/29/2015
 ******************************/

#ifndef __BASE_ARRAYLIST__
#define __BASE_ARRAYLIST__

#include "base/CCRef.h"
#include "FrameworkMacros.h"
#include <vector>
#include <string>

MW_FRAMEWORK_BEGIN

/**
 * Linear list data structure.
 */
class MW_DLL MWArrayList : public cocos2d::Ref
{
public:
    /**
     * Create an array structure.
     *
     * @return MWArrayList instance which is autoreleased.
     */
    static MWArrayList *create();
    
    /**
     * MWArrayList constructor.
     */
    MWArrayList();
    /**
     * MWArrayList destructor.
     */
    virtual ~MWArrayList();
    
    /**
     * Overload methods to append value to the list.
     *
     * @param val List value to append.
     */
    void appendObject(double val);
    void appendObject(bool val);
    void appendObject(const std::string &val);
    void appendObject(cocos2d::Ref *val);
    
    /**
     * Overload methods to set new value at the specified index.
     * @note If the index is out of range, it will throw an exception.
     *
     * @param val List value.
     * @param index List index.
     */
    void setObjectAtIndex(double val, MW_UINT index) MW_NOEXCEPTION(MW_WHETHER_THROW_EXCEPTION);
    void setObjectAtIndex(bool val, MW_UINT index) MW_NOEXCEPTION(MW_WHETHER_THROW_EXCEPTION);
    void setObjectAtIndex(const std::string &val, MW_UINT index) MW_NOEXCEPTION(MW_WHETHER_THROW_EXCEPTION);
    void setObjectAtIndex(cocos2d::Ref *val, MW_UINT index) MW_NOEXCEPTION(MW_WHETHER_THROW_EXCEPTION);
    
    /**
     * Overload methods to insert the value before the specified index.
     * @note If the index is out of range, it will throw an exception.
     *
     * @param val List value to add.
     * @param index List index to insert.
     */
    void insertObjectAtIndex(double val, MW_UINT index) MW_NOEXCEPTION(MW_WHETHER_THROW_EXCEPTION);
    void insertObjectAtIndex(bool val, MW_UINT index) MW_NOEXCEPTION(MW_WHETHER_THROW_EXCEPTION);
    void insertObjectAtIndex(const std::string &val, MW_UINT index) MW_NOEXCEPTION(MW_WHETHER_THROW_EXCEPTION);
    void insertObjectAtIndex(cocos2d::Ref *val, MW_UINT index) MW_NOEXCEPTION(MW_WHETHER_THROW_EXCEPTION);
    
    /**
     * Get the value at the specified index, it will throw an exception if the key doesn't exist.
     *
     * @param index List index.
     *
     * @return List value at the index.
     */
    double numberAtIndex(MW_UINT index) const MW_NOEXCEPTION(MW_WHETHER_THROW_EXCEPTION);
    bool booleanAtIndex(MW_UINT index) const MW_NOEXCEPTION(MW_WHETHER_THROW_EXCEPTION);
    std::string stringAtIndex(MW_UINT index) const MW_NOEXCEPTION(MW_WHETHER_THROW_EXCEPTION);
    cocos2d::Ref *objectAtIndex(MW_UINT index) const MW_NOEXCEPTION(MW_WHETHER_THROW_EXCEPTION);
    
    /**
     * Remove object at specified index, you will get a false if the index is out of range.
     *
     * @param key List index to remove.
     *
     * @return Remove result.
     */
    bool removeObjectAtIndex(MW_UINT index);
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
    std::vector<cocos2d::Ref*> _innerVector;
};

MW_FRAMEWORK_END

#endif /* defined(__BASE_ARRAYLIST__) */
