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
#if CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID
    // assets is a zip file, so you can't locate to such file path.
    Data fileData = FileUtils::getInstance()->getDataFromFile(filePath);
    string tmpPath = MWIOUtils::getInstance()->splicePath(FileUtils::getInstance()->getWritablePath(), "tmp");
    auto absolutePath = MWIOUtils::getInstance()->splicePath(tmpPath, filePath);
    size_t found = absolutePath.find_last_of("/\\");
    string tmpFilename = absolutePath.substr(found + 1);
    MWIOUtils::getInstance()->createDirectory(absolutePath.substr(0, found + 1));
    if (!MWIOUtils::getInstance()->writeDataToFile(fileData.getBytes(), fileData.getSize(), absolutePath)) {
        return false;
    }
#else
    auto absolutePath = FileUtils::getInstance()->fullPathForFilename(filePath);
#endif
    _filePath = absolutePath;
    _password = password;
    g_hUnz = unzOpen64(absolutePath.c_str());
    if (!g_hUnz) {
        return false;
    }
    unzClose(g_hUnz);
    g_hUnz = nullptr;
    
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