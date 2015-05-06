#include "MWIOUtils.h"

#if CC_TARGET_PLATFORM == CC_PLATFORM_IOS
#include "MWIOUtilsStrategyIOS.h"
#endif

using namespace std;

MW_FRAMEWORK_BEGIN

MWIOUtils::MWIOUtils()
#if CC_TARGET_PLATFORM == CC_PLATFORM_IOS
: _strategy(new MWIOUtilsStrategyIos())
#endif
{
}

MWIOUtils::~MWIOUtils()
{
    CC_SAFE_DELETE(_strategy);
}

string MWIOUtils::resourcePath(const std::string &path)
{
    if (_strategy) {
        return _strategy->resourcePath(path);
    }
    CCLOG("Unimplemented platform.");
    return "";
}

bool MWIOUtils::fileExists(const std::string &path)
{
    if (_strategy) {
        return _strategy->fileExists(path);
    }
    CCLOG("Unimplemented platform.");
    return false;
}

bool MWIOUtils::moveFile(const std::string &oldPath, const std::string &newPath)
{
    if (_strategy) {
        return _strategy->moveFile(oldPath, newPath);
    }
    CCLOG("Unimplemented platform.");
    return false;
}

bool MWIOUtils::copyFile(const std::string &oldPath, const std::string &newPath)
{
    if (_strategy) {
        return _strategy->copyFile(oldPath, newPath);
    }
    CCLOG("Unimplemented platform.");
    return false;
}

MWBinaryData *MWIOUtils::getDataFromFile(const std::string &filePath)
{
    if (_strategy) {
        return _strategy->getDataFromFile(filePath);
    }
    CCLOG("Unimplemented platform.");
    return nullptr;
}

bool MWIOUtils::writeDataToFile(const MW_RAW_DATA content, MW_ULONG length, const std::string &filePath, bool isAppend)
{
    if (_strategy) {
        return _strategy->writeDataToFile(content, length, filePath, isAppend);
    }
    CCLOG("Unimplemented platform.");
    return false;
}

bool MWIOUtils::removeFile(const std::string &filePath)
{
    if (_strategy) {
        return _strategy->removeFile(filePath);
    }
    CCLOG("Unimplemented platform.");
    return false;
}

bool MWIOUtils::createFile(const std::string &filePath)
{
    if (_strategy) {
        return _strategy->createFile(filePath);
    }
    CCLOG("Unimplemented platform.");
    return false;
}

bool MWIOUtils::createDirectory(const std::string &directoryPath)
{
    if (_strategy) {
        return _strategy->createDirectory(directoryPath);
    }
    CCLOG("Unimplemented platform.");
    return false;
}

MW_FRAMEWORK_END