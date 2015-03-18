/******************************
 Description: Framework macros
 Author: M.Wan
 Date: 1/28/2015
 ******************************/

#ifndef __FRAMEWORK_MACROS__
#define __FRAMEWORK_MACROS__

#define MW_DLL
#define MW_INTERFACE

/**
 * Basic types.
 */
#define MW_ULONG unsigned long
#define MW_UINT unsigned int
#define MW_USHORT unsigned short
#define MW_BYTE unsigned char
#define MW_RAW_DATA void *

/**
 * Mark as deprecated.
 */
#if defined(__GNUC__) && ((__GNUC__ >= 4) || ((__GNUC__ == 3) && (__GNUC_MINOR__ >= 1)))
#define MW_DEPRECATED __attribute__((deprecated))
#elif _MSC_VER >= 1400
#define MW_DEPRECATED __declspec(deprecated)
#else
#define MW_DEPRECATED
#endif

/**
 * Whether should throw an exception? default true.
 */
#define MW_WHETHER_THROW_EXCEPTION 1
#define MW_NOEXCEPTION(__EXPRESSION__) noexcept(__EXPRESSION__)
/**
 * Get the related error string of specified error code.
 */
#define MW_GET_ERROR_STRING(__ERROR_CODE__) mwframework::GetErrorString(__ERROR_CODE__)
/**
 * Throw framework defined exception with an existed error code.
 */
#define MW_THROW_EXCEPTION(__ERROR_CODE__) throw mwframework::MWException::create(__ERROR_CODE__, MW_GET_ERROR_STRING(__ERROR_CODE__));

/**
 * Framework namespace header.
 */
#define MW_FRAMEWORK_BEGIN namespace mwframework {
/**
 * Framework namespace tail.
 */
#define MW_FRAMEWORK_END }

/**
 * Make a class uncopyable.
 */
#define MW_UNCOPYABLE private mwframework::IUncopyable
/**
 * Make a class uninheritable.
 */
#define MW_UNINHERITABLE(__TYPE__) public mwframework::IUninheritable<__TYPE__>

/**
 * Make a class singleton.
 * @note You must implement the constructor of the class, even if it is just the default one.
 */
#define MW_SINGLETON(__TYPE__)	\
public:	\
static __TYPE__* getInstance()	\
{	\
static __TYPE__* _instance;	\
if (!_instance)	\
{	\
_instance = new __TYPE__();	\
}	\
return _instance;		\
}	\
protected:	\
__TYPE__();

/**
 * Inline methods macros.
 */
#define MW_SYNTHESIZE(__VAR_TYPE__, __VAR_NAME__, __FUNC_NAME__)    \
public: \
inline __VAR_TYPE__ get##__FUNC_NAME__() const  \
{   \
return __VAR_NAME__;    \
}   \
inline void set##__FUNC_NAME__(__VAR_TYPE__ var)    \
{   \
__VAR_NAME__ = var; \
}   \
protected:  \
__VAR_TYPE__ __VAR_NAME__;

#define MW_SYNTHESIZE_PASS_BY_CONST_REF(__VAR_TYPE__, __VAR_NAME__, __FUNC_NAME__)    \
public: \
inline __VAR_TYPE__ get##__FUNC_NAME__() const  \
{   \
return __VAR_NAME__;    \
}   \
inline void set##__FUNC_NAME__(const __VAR_TYPE__ &var)    \
{   \
__VAR_NAME__ = var; \
}   \
protected:  \
__VAR_TYPE__ __VAR_NAME__;

#define MW_SYNTHESIZE_READONLY(__VAR_TYPE__, __VAR_NAME__, __FUNC_NAME__)   \
public: \
inline __VAR_TYPE__ get##__FUNC_NAME__() const  \
{   \
    return __VAR_NAME__;    \
}   \
protected:  \
__VAR_TYPE__ __VAR_NAME__;

#define MW_SYNTHESIZE_RETAIN(__VAR_TYPE__, __VAR_NAME__, __FUNC_NAME__)    \
public: \
inline __VAR_TYPE__ get##__FUNC_NAME__() const  \
{   \
return __VAR_NAME__;    \
}   \
inline void set##__FUNC_NAME__(__VAR_TYPE__ var)    \
{   \
if (var != __VAR_NAME__) {  \
CC_SAFE_RELEASE(__VAR_NAME__);  \
__VAR_NAME__ = var; \
CC_SAFE_RETAIN(__VAR_NAME__);   \
}   \
}   \
protected:  \
__VAR_TYPE__ __VAR_NAME__;

// bind for c11 functional
#define MW_CALLBACK_0(__SELECTOR__,__TARGET__, ...) std::bind(&__SELECTOR__,__TARGET__, ##__VA_ARGS__)
#define MW_CALLBACK_1(__SELECTOR__,__TARGET__, ...) std::bind(&__SELECTOR__,__TARGET__, std::placeholders::_1, ##__VA_ARGS__)
#define MW_CALLBACK_2(__SELECTOR__,__TARGET__, ...) std::bind(&__SELECTOR__,__TARGET__, std::placeholders::_1, std::placeholders::_2, ##__VA_ARGS__)
#define MW_CALLBACK_3(__SELECTOR__,__TARGET__, ...) std::bind(&__SELECTOR__,__TARGET__, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3, ##__VA_ARGS__)

#define MW_SUPPORT_MULTITHREADING 0
/**
 * Threading mutex lock, unlock.
 */
#if MW_SUPPORT_MULTITHREADING
#else
#define MW_MUTEX_LOCK(__MUTEX__)
#define MW_MUTEX_UNLOCK(__MUTEX__)
#endif

#endif