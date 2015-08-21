#if CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID

#include "MWCrypto.h"

#include <jni.h>
#include "jni/JniHelper.h"

using namespace std;
using namespace cocos2d;

MW_FRAMEWORK_BEGIN

int MWCrypto::getAes256KeyLength()
{
    return 32;
}

int MWCrypto::cryptAes256(bool isDecrypt, unsigned char *input, int inputLength, unsigned char *output, int outputBufferLength, unsigned char *key, int keyLength)
{
	char buffer[keyLength + 1] = { 0 };
	memcpy(buffer, key, keyLength);
	string aesKey(buffer);
	string methodName = isDecrypt ? "decipherAes256" : "encipherAes256";
	JniMethodInfo t;
	if (JniHelper::getStaticMethodInfo(t, "org/cocos2dx/lua/AndroidUtils", methodName.c_str(), "([BLjava/lang/String;)[B"))
	{
		jbyteArray arg1 = t.env->NewByteArray(inputLength);
		t.env->SetByteArrayRegion(arg1, 0, inputLength, (jbyte *) input);
		jstring arg2 = t.env->NewStringUTF(aesKey.c_str());
		jbyteArray crypted = (jbyteArray) t.env->CallStaticObjectMethod(t.classID, t.methodID, arg1, arg2);
		jsize len = t.env->GetArrayLength(crypted);
		if (len + 1 > outputBufferLength)
		{
        	// output buffer too small
			return -1;
		}
		jbyte *bytes = t.env->GetByteArrayElements(crypted, nullptr);
		memcpy(output, bytes, len);
		output[len] = 0;
		
		return len;
	}
	return 0;
}

MW_FRAMEWORK_END

#endif