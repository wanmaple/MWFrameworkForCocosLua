#if CC_TARGET_PLATFORM == CC_PLATFORM_IOS

#include "MWCrypto.h"

#import <CommonCrypto/CommonCryptor.h>

MW_FRAMEWORK_BEGIN

int MWCrypto::getAes256KeyLength()
{
    return kCCKeySizeAES256;
}

int MWCrypto::cryptAes256(bool isDecrypt, unsigned char *input, int inputLength, unsigned char *output, int outputBufferLength, unsigned char *key, int keyLength)
{
    int maxKeyLength = getAes256KeyLength();
    unsigned char aesKey[maxKeyLength];
    memset(aesKey, 0, sizeof(aesKey));
    memcpy(aesKey, key, keyLength > maxKeyLength ? maxKeyLength : keyLength);
    
    int bufferSize = inputLength + kCCBlockSizeAES128;
    void *buffer = malloc(bufferSize);
    size_t dataUsed = 0;
    
    CCCryptorStatus status = CCCrypt(isDecrypt ? kCCDecrypt : kCCEncrypt,
                                     kCCAlgorithmAES128,
                                     kCCOptionPKCS7Padding | kCCOptionECBMode,
                                     aesKey, maxKeyLength,
                                     nullptr,
                                     input, inputLength,
                                     buffer, bufferSize,
                                     &dataUsed);
    
    if (status == kCCSuccess)
    {
        if (outputBufferLength >= dataUsed + 1)
        {
            memset(output, 0, outputBufferLength);
            memcpy(output, buffer, dataUsed);
            return (int) dataUsed;
        }
        // output buffer too small
        return -1;
    }
    
    switch (status)
    {
        case kCCParamError:
            CCLOG("[Crypto] cryptAes256(%s) param error", isDecrypt ? "Decrypt" : "Encrypt");
            break;
        case kCCBufferTooSmall:
            CCLOG("[Crypto] cryptAes256(%s) buffer too small", isDecrypt ? "Decrypt" : "Encrypt");
            break;
        case kCCMemoryFailure:
            CCLOG("[Crypto] cryptAes256(%s) memory failure", isDecrypt ? "Decrypt" : "Encrypt");
            break;
        case kCCAlignmentError:
            CCLOG("[Crypto] cryptAes256(%s) alignment error", isDecrypt ? "Decrypt" : "Encrypt");
            break;
        case kCCDecodeError:
            CCLOG("[Crypto] cryptAes256(%s) decode error", isDecrypt ? "Decrypt" : "Encrypt");
            break;
        case kCCUnimplemented:
            CCLOG("[Crypto] cryptAes256(%s) unimplemented", isDecrypt ? "Decrypt" : "Encrypt");
            break;
        default:
            CCLOG("[Crypto] cryptAes256(%s) unknown error", isDecrypt ? "Decrypt" : "Encrypt");
    }
    
    return 0;
}

MW_FRAMEWORK_END

#endif