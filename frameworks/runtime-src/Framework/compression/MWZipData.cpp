#include "MWZipData.h"

#include "cocos2d.h"
#include <new>

#include "minizip/unzip.h"

using namespace cocos2d;
using namespace std;

MW_FRAMEWORK_BEGIN

MW_LOCAL unzFile g_hZip = nullptr;
MW_LOCAL unz_global_info64 g_globalInfo;

MWZipData *MWZipData::createWithFile(const std::string &filePath, const std::string &password)
{
    auto pRet = new (nothrow) MWZipData();
    if (pRet && pRet->initWithFile(filePath, password)) {
        pRet->autorelease();
        return pRet;
    }
    CC_SAFE_RELEASE(pRet);
    return nullptr;
}

bool MWZipData::initWithFile(const std::string &filePath, const std::string &password)
{
    auto abosultePath = FileUtils::getInstance()->fullPathForFilename(filePath);
    g_hZip = unzOpen64(abosultePath.c_str());
    if (!g_hZip) {
        return false;
    }
    int result = unzGetGlobalInfo64(g_hZip, &g_globalInfo);
    if (result != UNZ_OK) {
        unzClose(g_hZip);
        g_hZip = nullptr;
        return false;
    }
    
    _password = password;
    
    return true;
}

MWZipData::MWZipData()
: _password()
{
    
}

MWZipData::~MWZipData()
{
    if (g_hZip) {
        unzClose(g_hZip);
        g_hZip = nullptr;
    }
}

MWBinaryData *MWZipData::getCompressedFileData(const std::string &compressedFile)
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
    if (_password.size() > 0) {
        result = unzOpenCurrentFilePassword(g_hZip, _password.c_str());
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
        int size = unzReadCurrentFile(g_hZip, data, dataSize);
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

MW_FRAMEWORK_END