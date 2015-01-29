/******************************
 Description: Exception base.
 Author: M.Wan
 Date: 1/29/2015
 ******************************/

#ifndef __BASE_EXCEPTION__
#define __BASE_EXCEPTION__

#include "base/CCRef.h"
#include "FrameworkMacros.h"
#include <exception>
#include <string>

MW_FRAMEWORK_BEGIN

class MW_DLL MWException : public cocos2d::Ref, public std::exception
{
public:
    /**
     * Create MWException object.
     *
     * @param errCode Error code.
     * @param msg Error message.
     *
     * @return MWException instance which is autoreleased.
     */
    static MWException *create(int errCode, const char *msg);
    
    /**
     * MWException constructor.
     *
     * @param errCode Error code.
     * @param msg Error message.
     */
    MWException(int errCode, const char *msg);
    virtual ~MWException() {}
    
    /**
     * Get error code.
     *
     * @return Error code of the exception.
     */
    inline int errorCode() const
    {
        return _errorCode;
    }
    
    /**
     * std::exception overrides.
     */
    virtual const char *what() const _NOEXCEPT override;
    
protected:
    int _errorCode;
    std::string _errorMsg;
};

MW_FRAMEWORK_END

#endif /* defined(__BASE_EXCEPTION__) */
