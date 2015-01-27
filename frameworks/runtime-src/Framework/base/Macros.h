/******************************
 Description: Define some macros
 Author: M.Wan
 Date: 8/3/2014
 ******************************/

#ifndef __MACROS__
#define __MACROS__

#define MWDLL

/**
 * Basic types
 */
#define MW_ULONG unsigned long
#define MW_UINT unsigned int
#define MW_USHORT unsigned short
#define MW_BYTE unsigned char

/**
 * Make a class singleton
 * @note You must implement the constructor of the class, even if it is just the default one.
 */
#define SINGLETON(__TYPE__)		\
public:		\
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

#endif
