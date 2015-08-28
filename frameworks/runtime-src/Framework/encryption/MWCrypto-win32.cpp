#if CC_TARGET_PLATFORM == CC_PLATFORM_WIN32

#include "MWCrypto.h"

using namespace std;
using namespace cocos2d;

MW_FRAMEWORK_BEGIN

int MWCrypto::getAes256KeyLength()
{
    return 32;
}

int MWCrypto::cryptAes256(bool isDecrypt, unsigned char *input, int inputLength, unsigned char *output, int outputBufferLength, unsigned char *key, int keyLength)
{
	return 0;
}

MW_FRAMEWORK_END

#endif