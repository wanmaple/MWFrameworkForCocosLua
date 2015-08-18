#include "MWUUIDGenerator.h"

using namespace std;

#if CC_TARGET_PLATFORM == CC_PLATFORM_IOS
#include <uuid/uuid.h>
#endif

typedef struct {
    unsigned long Data1;
    unsigned short Data2;
    unsigned short Data3;
    unsigned char Data4[8];
} GUID, UUID;

MW_FRAMEWORK_BEGIN

MW_LOCAL GUID CreateGUID()
{
    GUID guid;
#if CC_TARGET_PLATFORM == CC_PLATFORM_IOS
    ::uuid_generate(reinterpret_cast<unsigned char*>(&guid));
#endif
    return guid;
}

MW_LOCAL string GuidToString(const GUID &guid)
{
    char buffer[64] = { 0 };
    ::snprintf(
    buffer, sizeof(buffer), "%08X%04X%04X%02X%02X%02X%02X%02X%02X%02X%02X", guid.Data1, guid.Data2, guid.Data3, guid.Data4[0], guid.Data4[1], guid.Data4[2], guid.Data4[3], guid.Data4[4], guid.Data4[5], guid.Data4[6], guid.Data4[7]);
               
    return string(buffer);
}

string MWUUIDGenerator::generateUUID()
{
    return GuidToString(CreateGUID());
}
               
MWUUIDGenerator::MWUUIDGenerator()
{

}

MW_FRAMEWORK_END