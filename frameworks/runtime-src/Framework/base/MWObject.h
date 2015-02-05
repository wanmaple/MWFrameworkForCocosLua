/******************************
 Description: Base object, for some extension features.
 Author: M.Wan
 Date: 1/28/2015
 ******************************/

#ifndef __BASE_OBJECT__
#define __BASE_OBJECT__

#include "cocos2d.h"
#include "FrameworkMacros.h"

MW_FRAMEWORK_BEGIN

/**
 * Base object of the framework, excludes UI related nodes.
 */
class MW_DLL MWObject : public cocos2d::Ref
{
public:
    /**
     * MWObject destructor.
     */
    virtual ~MWObject();
    
    /**
     * Simply generate an unique value(by using its address).
     */
    virtual int hash();
    
protected:
    MWObject();
    
#if CC_ENABLE_SCRIPT_BINDING
    cocos2d::ccScriptType _scriptType;         // type of script binding, lua or javascript
#endif
};

MW_FRAMEWORK_END

#endif /* defined(__BASE_OBJECT__) */
