#if CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID

#include "MWUUIDGenerator.h"

#include <jni.h>
#include "jni/JniHelper.h"

using namespace std;
using namespace cocos2d;

MW_FRAMEWORK_BEGIN

string MWUUIDGenerator::generateUUID()
{
	JniMethodInfo t;
	if (JniHelper::getStaticMethodInfo(t, "java/util/UUID", "randomUUID", "()Ljava/util/UUID;")) 
	{
		jobject javaUuid = t.env->CallStaticObjectMethod(t.classID, t.methodID);
		if (JniHelper::getMethodInfo(t, "java/util/UUID", "toString", "()Ljava/lang/String;"))
		{
			jstring javaStr = (jstring) t.env->CallObjectMethod(javaUuid, t.methodID);
			string uuid = JniHelper::jstring2string(javaStr);
			// erase '-'
			size_t found;
			while ((found = uuid.find_first_of('-')) != string::npos)
			{
				uuid.erase(found, 1);
			}
			return uuid;
		}
	}
    return "";
}
               
MWUUIDGenerator::MWUUIDGenerator()
{
}

MW_FRAMEWORK_END

#endif