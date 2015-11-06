#if CC_TARGET_PLATFORM == CC_PLATFORM_WIN32

#include "MWUUIDGenerator.h"

#include <ObjBase.h>

using namespace std;
using namespace cocos2d;

MW_FRAMEWORK_BEGIN

string MWUUIDGenerator::generateUUID()
{
	GUID guid;
	::CoCreateGuid(&guid);

	char buffer[64] = { 0 };
#ifdef __GNUC__
	::snprintf(
#else	// msvc
	::_snprintf_s(
#endif
		buffer, sizeof(buffer), "%08X%04X%04X%02X%02X%02X%02X%02X%02X%02X%02X", guid.Data1, guid.Data2, guid.Data3, guid.Data4[0], guid.Data4[1], guid.Data4[2], guid.Data4[3], guid.Data4[4], guid.Data4[5], guid.Data4[6], guid.Data4[7]);

	return string(buffer);
}
               
MWUUIDGenerator::MWUUIDGenerator()
{
}

MW_FRAMEWORK_END

#endif