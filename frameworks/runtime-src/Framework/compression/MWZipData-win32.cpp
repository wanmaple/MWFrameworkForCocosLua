#include "MWZipData.h"

#include "cocos2d.h"
#include <new>

#include "../platform/MWIOUtils.h"

#include "zip-win32/zip.h"
#include "zip-win32/unzip.h"

#define INVALID_ZIP_HANDLE 0

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
MW_LOCAL ZIPENTRY g_zEntry;

MWZipData *MWZipData::createWithExistingFile(const std::string &filePath, const std::string &password)
{
    auto pRet = new (nothrow) MWZipData();
    if (pRet && pRet->initWithExistingFile(filePath, password)) {
        pRet->autorelease();
        return pRet;
    }
    CC_SAFE_RELEASE(pRet);
    return nullptr;
}

bool MWZipData::initWithExistingFile(const std::string &filePath, const std::string &password)
{
	string absolutePath = FileUtils::getInstance()->fullPathForFilename(filePath);
	if (!MWIOUtils::getInstance()->fileExists(absolutePath))
	{
		return false;
	}
	_filePath = absolutePath;
	_password = password;

	wchar_t buffer[MAX_PATH] = { 0 };
	STDSTRING_TO_WCHAR(absolutePath, buffer);
	g_hZip = OpenZip(buffer, password.c_str());
	if (g_hZip == INVALID_ZIP_HANDLE)
	{
		return false;
	}
	CloseZip(g_hZip);
    return true;
}

MWZipData *MWZipData::createWithNewFile(const std::string &filePath, const std::string &password)
{
    auto pRet = new (nothrow) MWZipData();
    if (pRet && pRet->initWithNewFile(filePath, password)) {
        pRet->autorelease();
        return pRet;
    }
    CC_SAFE_RELEASE(pRet);
    return nullptr;
}

bool MWZipData::initWithNewFile(const std::string &filePath, const std::string &password)
{
	string absolutePath = FileUtils::getInstance()->fullPathForFilename(filePath);
	string dirPath = absolutePath.substr(0, absolutePath.find_last_of("/\\"));
	MWIOUtils::getInstance()->createDirectory(dirPath);
	_filePath = absolutePath;
	_password = password;

	wchar_t buffer[MAX_PATH] = { 0 };
	STDSTRING_TO_WCHAR(absolutePath, buffer);
	g_hZip = CreateZip(buffer, password.c_str());
	if (g_hZip == INVALID_ZIP_HANDLE)
	{
		return false;
	}
	CloseZip(g_hZip);

    return true;
}

MWZipData *MWZipData::createWithBinaryData(MWBinaryData *rawData, const std::string &password)
{
	auto pRet = new (nothrow)MWZipData();
	if (pRet && pRet->initWithBinaryData(rawData, password)) {
		pRet->autorelease();
		return pRet;
	}
	CC_SAFE_RELEASE(pRet);
	return nullptr;
}

bool MWZipData::initWithBinaryData(MWBinaryData *rawData, const std::string &password)
{
	_filePath = "";
	_password = password;
	g_hZip = OpenZip(rawData->getData(), rawData->getSize(), password.c_str());
	if (g_hZip == INVALID_ZIP_HANDLE)
	{
		return false;
	}
	CloseZip(g_hZip);
	return true;
}

MWZipData::MWZipData()
{
}

MWZipData::~MWZipData()
{
	if (g_hZip)
	{
		CloseZip(g_hZip);
	}
}

void MWZipData::beginUnzip()
{
	wchar_t buffer[MAX_PATH] = { 0 };
	STDSTRING_TO_WCHAR(_filePath, buffer);
	g_hZip = OpenZip(buffer, _password.c_str());
}

void MWZipData::endUnzip()
{
	CloseZip(g_hZip);
	g_hZip = INVALID_ZIP_HANDLE;
}

MWBinaryData *MWZipData::getCompressedFileData(const std::string &compressedFile)
{
	wchar_t buffer[MAX_PATH] = { 0 };
	STDSTRING_TO_WCHAR(compressedFile, buffer);
	int index;
	ZRESULT res = FindZipItem(g_hZip, buffer, true, &index, &g_zEntry);
	if (res != ZR_OK)
	{
		return nullptr;
	}
	MW_ULONG dataSize = g_zEntry.unc_size;
	MW_BYTE *data = (MW_BYTE *)malloc(dataSize);
	res = UnzipItem(g_hZip, index, data, dataSize);
	if (res != ZR_OK)
	{
		if (data)
		{
			free(data);
		}
		return nullptr;
	}
	auto binaryData = MWBinaryData::create(data, dataSize);
	if (data)
	{
		free(data);
	}

	return binaryData;
}

void MWZipData::beginZip()
{
	wchar_t buffer[MAX_PATH] = { 0 };
	STDSTRING_TO_WCHAR(_filePath, buffer);
	if (MWIOUtils::getInstance()->fileExists(_filePath))
	{
		g_hZip = OpenZip(buffer, _password.c_str());
	}
	else
	{
		g_hZip = CreateZip(buffer, _password.c_str());
	}
	GetZipItem(g_hZip, -1, &g_zEntry);
}

void MWZipData::endZip()
{
	CloseZip(g_hZip);
	g_hZip = INVALID_ZIP_HANDLE;
}

bool MWZipData::zipNewFile(const std::string &name, mwframework::MWBinaryData *fileData, int level)
{
	wchar_t filename[MAX_PATH] = { 0 };
	STDSTRING_TO_WCHAR(name, filename);
	ZRESULT res = ZipAdd(g_hZip, filename, fileData->getData(), fileData->getSize());
	if (res != ZR_OK)
	{
		return false;
	}
	return true;
}

MW_FRAMEWORK_END