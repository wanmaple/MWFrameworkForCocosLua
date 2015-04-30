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

MW_LOCAL unzFile g_hZip = nullptr;
MW_LOCAL unz_global_info64 g_globalInfo;

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
    auto absolutePath = FileUtils::getInstance()->fullPathForFilename(filePath);
    g_hZip = unzOpen64(absolutePath.c_str());
    if (!g_hZip) {
        return false;
    }
    int result = unzGetGlobalInfo64(g_hZip, &g_globalInfo);
    if (result != UNZ_OK) {
        unzClose(g_hZip);
        g_hZip = nullptr;
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
    if (!MWIOUtils::getInstance()->fileExists(filePath)) {
        if (!MWIOUtils::getInstance()->createFile(filePath)) {
            return false;
        }
        return this->initWithExistingFile(filePath);
    }
    return false;
}

MWZipData::MWZipData()
{
    
}

MWZipData::~MWZipData()
{
    if (g_hZip) {
        unzClose(g_hZip);
        g_hZip = nullptr;
    }
}

MWBinaryData *MWZipData::getCompressedFileData(const std::string &compressedFile, const std::string &password)
{
    unz_file_info64 fi;
    // locate file.
    int result = unzLocateFile(g_hZip, compressedFile.c_str(), false);
    if (result != UNZ_OK) {
        return nullptr;
    }
    result = unzGetCurrentFileInfo64(g_hZip, &fi, const_cast<char *>(compressedFile.c_str()), compressedFile.size(), nullptr, 0, nullptr, 0);
    if (result != UNZ_OK) {
        return nullptr;
    }
    // only consider file.
    if (password.size() > 0) {
        result = unzOpenCurrentFilePassword(g_hZip, password.c_str());
    } else {
        result = unzOpenCurrentFile(g_hZip);
    }
    if (result != UNZ_OK) {
        return nullptr;
    }
    MW_ULONG dataSize = fi.uncompressed_size;
    MW_BYTE *data = (MW_BYTE *) malloc(dataSize);
    // read the data.
    while (true) {
        int size = unzReadCurrentFile(g_hZip, data, (MW_UINT) dataSize);
        if (size < 0) {
            free(data);
            unzCloseCurrentFile(g_hZip);
            return nullptr;
        } else if (size == 0) {
            break;
        }
    }
    unzCloseCurrentFile(g_hZip);
    
    auto pBinaryData = MWBinaryData::create(data, dataSize);
    
    return pBinaryData;
}

bool MWZipData::zipNewFile(const std::string &name, mwframework::MWBinaryData *fileData, const std::string &password, int level)
{
    if (name.size() <= 0 || !fileData || !fileData->isValid()) {
        return false;
    }
    if (level < 0) {
        level = 0;
    } else if (level > 9) {
        level = 9;
    }
    
    zip_fileinfo fi = { 0 };
    int result = zipOpenNewFileInZip4(g_hZip, name.c_str(), &fi, nullptr, 0, nullptr, 0, nullptr, Z_DEFAULT_COMPRESSION, level, 0, -MAX_WBITS, DEF_MEM_LEVEL, Z_DEFAULT_STRATEGY, (password.size() > 0 ? password.c_str() : nullptr), 0, 0, 0);
    if (result != UNZ_OK) {
        return false;
    }
    
    return zipWriteInFileInZip(g_hZip, fileData->getData(), (MW_UINT) fileData->getSize());
}

MW_FRAMEWORK_END