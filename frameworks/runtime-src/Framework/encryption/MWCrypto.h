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

class MW_DLL MWCrypto
{
    MW_SINGLETON(MWCrypto);
public:
    // md5
    std::string md5(MWBinaryData *data);
    std::string md5String(const std::string &content);
    std::string md5File(const std::string &filePath);
    // base64
    std::string encodeBase64(const std::string &content);
    std::string decodeBase64(const std::string &content);
    // aes
    int getAes256KeyLength();
    MWBinaryData *encipherAes256(MWBinaryData *data, const std::string &key);
    MWBinaryData *decipherAes256(MWBinaryData *data, const std::string &key);
    // xxtea
    MWBinaryData *encipherXxtea(MWBinaryData *data, const std::string &key);
    MWBinaryData *decipherXxtea(MWBinaryData *data, const std::string &key);
    
protected:
    char *bin2hex(MW_RAW_DATA bin, int length);
    
    int cryptAes256(bool isDecrypt, unsigned char* input,
                    int inputLength,
                    unsigned char* output,
                    int outputBufferLength,
                    unsigned char* key,
                    int keyLength);
};

MW_FRAMEWORK_END

#endif /* defined(__ENCRYPTION_CIPHER_MACHINE__) */
