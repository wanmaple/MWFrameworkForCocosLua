/******************************
 Description: Stack structure.
 Author: M.Wan
 Date: 1/30/2015
 ******************************/

#ifndef __BASE_STACK__
#define __BASE_STACK__

#include "MWObject.h"
#include "FrameworkMacros.h"
#include "ICloneable.h"
#include <vector>
#include <string>

MW_FRAMEWORK_BEGIN

/**
 * Stack data structure.
 */
class MW_DLL MWStack : public MWObject, public ICloneable<MWStack>
{
public:
    /**
     * Create a stack structure.
     *
     * @return MWStack instance which is autoreleased.
     */
    static MWStack *create();
    
    /**
     * MWStack constructor.
     */
    MWStack();
    /**
     * MWStack destructor.
     */
    virtual ~MWStack();
    
    /**
     * Push value to the stack top.
     *
     * @param val Stack value.
     */
    void push(cocos2d::Ref *val);
    /**
     * Pop the top the stack.
     * @note It will return false if the stack is empty.
     *
     * @return Popped result.
     */
    bool pop();
    /**
     * Get the top of the stack.
     * @note It will return nullptr if the stack is empty.
     *
     * @return The top of the stack.
     */
    cocos2d::Ref *top();
    
    /**
     * Clear all objects.
     */
    void clear();
    
    /**
     * Get the elements count of the stack.
     */
    inline MW_UINT count()
    {
        return _innerStack.size();
    }
    /**
     * Whether the stack is empty?
     */
    inline bool empty()
    {
        return _innerStack.empty();
    }
    
    /**
     * ICloneable overrides.
     */
    virtual MWStack *clone() override;
    
protected:
    std::vector<cocos2d::Ref*> _innerStack;
};

MW_FRAMEWORK_END

#endif /* defined(__BASE_STACK__) */
