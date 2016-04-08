#include "MWZipData.h"

#include "cocos2d.h"
#include <new>

#include "../platform/MWIOUtils.h"

// minizip lib
#include "minizip/zip.h"
#include "minizip/unzip.h"

using namespace cocos2d;
using namespace std;

MW_FRAMEWORK_BEGIN

typedef struct
{
	MW_RAW_DATA data;
	ZPOS64_T size;
	ZPOS64_T current;
} ZIPINFO, *PZIPINFO;

static voidpf ZCALLBACK OpenZipFile(voidpf opaque, const void *filename, int mode)
{
	const char *filePath = reinterpret_cast<const char *>(filename);
	PZIPINFO zipInfo = (PZIPINFO)opaque;
	if (!filePath || strlen(filePath) > 0)
	{
		// maybe is android file path?
		Data zipData = FileUtils::getInstance()->getDataFromFile(filename);
		CCASSERT(!zipData.isNull(), "Invalid zip data.")
		voidpf buffer = malloc(zipData.getSize());
		memcpy(buffer, zipData.getBytes(), zipData.getSize());
		// save zip info
		zipInfo->data = buffer;
		zipInfo->size = zipData.getSize();
	}
	else
	{
		// filename no use and the zip info should be inited.
	}
	zipInfo->current = 0;

	return zipInfo->data;
}

static uLong ZCALLBACK ReadZipFile(voidpf opaque, voidpf stream, void *buf, uLong size)
{
	PZIPINFO zipInfo = (PZIPINFO)opaque;
	stream = (MW_RAW_DATA)((MW_BYTE *)stream + zipInfo->current);
	memcpy(buf, stream, size);
	zipInfo->current += size;

	return size;
}

static uLong ZCALLBACK WriteZipFile(voidpf opaque, voidpf stream, const void *buf, uLong size)
{
	PZIPINFO zipInfo = (PZIPINFO)opaque;
	stream = (MW_RAW_DATA)((MW_BYTE *)stream + zipInfo->current);
	memcpy(stream, buf, size);
	zipInfo->current += size;

	return size;
}

static ZPOS64_T ZCALLBACK TellZipFile(voidpf opaque, voidpf stream)
{
	PZIPINFO zipInfo = (PZIPINFO)opaque;

	return zipInfo->size;
}

static int ZCALLBACK CloseZipFile(voidpf opaque, voidpf stream)
{
	PZIPINFO zipInfo = (PZIPINFO)opaque;
	MW_SAFE_DELETE(zipInfo);
	if (stream)
	{
		free(stream);
	}

	return 0;
}

static int ZCALLBACK ErrorZipFile(voidpf opaque, voidpf stream)
{
	// no error
	return 0;
}

static long ZCALLBACK SeekZipFile(voidpf opaque, voidpf stream, ZPOS64_T offset, int origin)
{
	PZIPINFO zipInfo = (PZIPINFO)opaque;
	switch (origin)
	{
	case ZLIB_FILEFUNC_SEEK_CUR:
		if (zipInfo->current + offset > zipInfo->size)
		{
			return -1;
		}
		zipInfo->current += offset;
		break;
	case ZLIB_FILEFUNC_SEEK_END:
		// no use
		zipInfo->current = zipInfo->size - 1;
		break;
	case ZLIB_FILEFUNC_SEEK_SET:
		if (offset > zipInfo->size)
		{
			return -1;
		}
		zipInfo->current = offset;
		break;
	default:
		return -1;
	}
	
	return 0;
}

MW_LOCAL zipFile g_hZip = nullptr;
MW_LOCAL unzFile g_hUnz = nullptr;

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
	auto absolutePath = FileUtils::getInstance()->fullPathForFilename(filePath);
	_filePath = absolutePath;
	_password = password;

#if CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID
    // assets is a zip file, so you can't locate to such file path.
	zlib_filefunc64_def ffunc;
	ffunc.zopen64_file = &OpenZipFile;
	ffunc.zread_file = &ReadZipFile;
	ffunc.zwrite_file = &WriteZipFile;
	ffunc.ztell64_file = &TellZipFile;
	ffunc.zseek64_file = &SeekZipFile;
	ffunc.zclose_file = &CloseZipFile;
	ffunc.zerror_file = &ErrorZipFile;
	ffunc.opaque = new ZIPINFO();
	g_hUnz = unzOpen2_64(filePath.c_str(), &ffunc);
#else
    g_hUnz = unzOpen64(absolutePath.c_str());
    if (!g_hUnz) {
        return false;
    }
    unzClose(g_hUnz);
    g_hUnz = nullptr;
    
    return true;
#endif
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
    auto absolutePath = MWIOUtils::getInstance()->resourcePath(filePath);
    _filePath = absolutePath;
    g_hZip = zipOpen64(absolutePath.c_str(), 0);
    if (!g_hZip) {
        return false;
    }
    zipClose(g_hZip, nullptr);
    g_hZip = nullptr;
    
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

	zlib_filefunc64_def ffunc;
	ffunc.zopen64_file = &OpenZipFile;
	ffunc.zread_file = &ReadZipFile;
	ffunc.zwrite_file = &WriteZipFile;
	ffunc.ztell64_file = &TellZipFile;
	ffunc.zseek64_file = &SeekZipFile;
	ffunc.zclose_file = &CloseZipFile;
	ffunc.zerror_file = &ErrorZipFile;
	ffunc.opaque = new ZIPINFO();
	ffunc.opaque->data = malloc(rawData->getSize());
	memcpy(ffunc.opaque->data, rawData->getData(), rawData->getSize());
	ffunc.opaque->size = rawData->getSize();

	g_hUnz = unzOpen2_64(nullptr, &ffunc);
	if (g_hUnz == INVALID_ZIP_HANDLE)
	{
		return false;
	}
	CloseZip(g_hUnz);
	return true;
}

MWZipData::MWZipData()
{
    
}

MWZipData::~MWZipData()
{
    if (g_hUnz) {
        unzClose(g_hUnz);
        g_hUnz = nullptr;
    }
    if (g_hZip) {
        zipClose(g_hZip, nullptr);
        g_hZip = nullptr;
    }
}

void MWZipData::beginUnzip()
{
    g_hUnz = unzOpen64(_filePath.c_str());
}

void MWZipData::endUnzip()
{
    unzClose(g_hUnz);
    g_hUnz = nullptr;
}

MWBinaryData *MWZipData::getCompressedFileData(const std::string &compressedFile)
{
    if (!g_hUnz) {
        CCLOG("Did you call the beginUnzip at first?");
        return nullptr;
    }
    
    unz_file_info64 fi;
    // locate file.
    int result = unzLocateFile(g_hUnz, compressedFile.c_str(), false);
    if (result != UNZ_OK) {
        return nullptr;
    }
    result = unzGetCurrentFileInfo64(g_hUnz, &fi, const_cast<char *>(compressedFile.c_str()), compressedFile.size(), nullptr, 0, nullptr, 0);
    if (result != UNZ_OK) {
        return nullptr;
    }
    // only consider file.
    if (_password.size() > 0) {
        result = unzOpenCurrentFilePassword(g_hUnz, _password.c_str());
    } else {
        result = unzOpenCurrentFile(g_hUnz);
    }
    if (result != UNZ_OK) {
        return nullptr;
    }
    MW_ULONG dataSize = fi.uncompressed_size;
    MW_BYTE *data = (MW_BYTE *) malloc(dataSize);
    // read the data.
    while (true) {
        int size = unzReadCurrentFile(g_hUnz, data, (MW_UINT) dataSize);
        if (size < 0) {
            free(data);
            unzCloseCurrentFile(g_hZip);
            return nullptr;
        } else if (size == 0) {
            break;
        }
    }
    unzCloseCurrentFile(g_hUnz);
    
    auto pBinaryData = MWBinaryData::create(data, dataSize);
    
    return pBinaryData;
}

void MWZipData::beginZip()
{
    g_hZip = zipOpen64(_filePath.c_str(), 0);
}

void MWZipData::endZip()
{
    zipClose(g_hZip, nullptr);
    g_hZip = nullptr;
}

bool MWZipData::zipNewFile(const std::string &name, mwframework::MWBinaryData *fileData, int level)
{
    if (name.size() <= 0 || !fileData || !fileData->isValid()) {
        return false;
    }
    if (level < 0) {
        level = 0;
    } else if (level > 9) {
        level = 9;
    }
    
    if (!g_hZip) {
        CCLOG("Did you call the beginZip at first?");
        return false;
    }
    
    zip_fileinfo fi = { 0 };
    int result = zipOpenNewFileInZip4(g_hZip, name.c_str(), &fi, nullptr, 0, nullptr, 0, nullptr, Z_DEFLATED, level, 0, -MAX_WBITS, DEF_MEM_LEVEL, Z_DEFAULT_STRATEGY, (_password.size() > 0 ? _password.c_str() : nullptr), 0, 0, 0);
    if (result != UNZ_OK) {
        return false;
    }
    
    result = zipWriteInFileInZip(g_hZip, fileData->getData(), (MW_UINT) fileData->getSize());
    zipCloseFileInZip(g_hZip);
    
    return result;
}

MW_FRAMEWORK_END