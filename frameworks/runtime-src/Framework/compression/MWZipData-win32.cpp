#include "MWZipData.h"

#include "cocos2d.h"
#include <new>

#include "../platform/MWIOUtils.h"

#include "zip-win32/zip.h"
#include "zip-win32/unzip.h"

#define STDSTRING_TO_WCHAR(__STR__, __BUFFER__)		\
for (int i = 0; i < (__STR__).size(); i++)	\
{	\
	(__BUFFER__)[i] = (__STR__)[i];	\
}

using namespace cocos2d;
using namespace std;

/**
* Reference: http://blog.csdn.net/wangqinghao/article/details/7060003
*/

MW_FRAMEWORK_BEGIN

MW_LOCAL HZIP g_hZip = nullptr;

MWZipData *MWZipData::createWithExistingFile(const std::string &filePath)
{
    auto pRet = new (nothrow) MWZipData();
    if (pRet && pRet->initWithExistingFile(filePath)) {
        pRet->autorelease();
        return pRet;
    }
    CC_SAFE_RELEASE(pRet);
    return nullptr;
}

bool MWZipData::initWithExistingFile(const std::string &filePath)
{
	if (!MWIOUtils::getInstance()->fileExists(filePath))
	{
		return false;
	}
    return true;
}

MWZipData *MWZipData::createWithNewFile(const std::string &filePath)
{
    auto pRet = new (nothrow) MWZipData();
    if (pRet && pRet->initWithNewFile(filePath)) {
        pRet->autorelease();
        return pRet;
    }
    CC_SAFE_RELEASE(pRet);
    return nullptr;
}

bool MWZipData::initWithNewFile(const std::string &filePath)
{
    return true;
}

MWZipData::MWZipData()
{
}

MWZipData::~MWZipData()
{
}

void MWZipData::beginUnzip()
{
}

void MWZipData::endUnzip()
{
}

MWBinaryData *MWZipData::getCompressedFileData(const std::string &compressedFile, const std::string &password)
{
	return nullptr;
}

void MWZipData::beginZip()
{
}

void MWZipData::endZip()
{
}

bool MWZipData::zipNewFile(const std::string &name, mwframework::MWBinaryData *fileData, const std::string &password, int level)
{
	return false;
}

MW_FRAMEWORK_END