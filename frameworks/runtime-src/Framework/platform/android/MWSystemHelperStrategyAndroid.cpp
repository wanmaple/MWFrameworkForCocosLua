#if CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID

#include "MWSystemHelperStrategyAndroid.h"

#include <jni.h>
#include "jni/JniHelper.h"

using namespace std;
using namespace cocos2d;

MW_FRAMEWORK_BEGIN

void MWSystemHelperStrategyAndroid::copyToPasteBoard(const std::string &content)
{
	JniMethodInfo t;
	if (JniHelper::getStaticMethodInfo(t, "org/cocos2dx/lua/AndroidUtils", "copyToPasteBoard", "(Ljava/lang/String;)V")) 
	{
		t.env->CallStaticVoidMethod(t.classID, t.methodID, t.env->NewStringUTF(content.c_str()));
	}
}

double MWSystemHelperStrategyAndroid::getCurrentUsedMemory()
{
	JniMethodInfo t;
	if (JniHelper::getStaticMethodInfo(t, "org/cocos2dx/lua/AndroidUtils", "getCurrentUsedMemory", "()D")) 
	{
		double mem = t.env->CallStaticDoubleMethod(t.classID, t.methodID);
		return mem;
	}
	return 0;
}

ENetStatus MWSystemHelperStrategyAndroid::checkNetStatus()
{
	JniMethodInfo t;
	if (JniHelper::getStaticMethodInfo(t, "org/cocos2dx/lua/AndroidUtils", "checkNetStatus", "()I")) 
	{
		int st = t.env->CallStaticIntMethod(t.classID, t.methodID);
		return (ENetStatus) st;
	}
	return ENetStatus::NO_NETWORK;
}

MW_FRAMEWORK_END

#endif