/******************************
 Description: Machine for ciphering and deciphering.
 Author: M.Wan
 Date: 6/10/2015
 ******************************/

#ifndef __ENCRYPTION_CIPHER_MACHINE__
#define __ENCRYPTION_CIPHER_MACHINE__

#include "../base/mwbase.h"
#include <string>

MW_FRAMEWORK_BEGIN

class MW_DLL MWCipherMachine
{
    MW_SINGLETON(MWCipherMachine);
public:
    std::string encipherMd5(const std::string &content);
    std::string decipherMd5(const std::string &content);
};

MW_FRAMEWORK_END

#endif /* defined(__ENCRYPTION_CIPHER_MACHINE__) */
