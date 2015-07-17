#include "MWIOUtils.h"

#if CC_TARGET_PLATFORM == CC_PLATFORM_IOS
#include "ios/MWIOUtilsStrategyIOS.h"
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
    MW_THROW_EXCEPTION(1012);
}

bool MWIOUtils::fileExists(const std::string &path)
{
    if (_strategy) {
        return _strategy->fileExists(path);
    }
    MW_THROW_EXCEPTION(1012);
}

bool MWIOUtils::moveFile(const std::string &oldPath, const std::string &newPath)
{
    if (_strategy) {
        return _strategy->moveFile(oldPath, newPath);
    }
    MW_THROW_EXCEPTION(1012);
}

bool MWIOUtils::copyFile(const std::string &oldPath, const std::string &newPath)
{
    if (_strategy) {
        return _strategy->copyFile(oldPath, newPath);
    }
    MW_THROW_EXCEPTION(1012);
}

MWBinaryData *MWIOUtils::getDataFromFile(const std::string &filePath)
{
    if (_strategy) {
        return _strategy->getDataFromFile(filePath);
    }
    MW_THROW_EXCEPTION(1012);
}

bool MWIOUtils::writeDataToFile(const MW_RAW_DATA content, MW_ULONG length, const std::string &filePath, bool isAppend)
{
    if (_strategy) {
        return _strategy->writeDataToFile(content, length, filePath, isAppend);
    }
    MW_THROW_EXCEPTION(1012);
}

bool MWIOUtils::removeFile(const std::string &filePath)
{
    if (_strategy) {
        return _strategy->removeFile(filePath);
    }
    MW_THROW_EXCEPTION(1012);
}

bool MWIOUtils::createFile(const std::string &filePath)
{
    if (_strategy) {
        return _strategy->createFile(filePath);
    }
    MW_THROW_EXCEPTION(1012);
}

bool MWIOUtils::createDirectory(const std::string &directoryPath)
{
    if (_strategy) {
        return _strategy->createDirectory(directoryPath);
    }
    MW_THROW_EXCEPTION(1012);
}

std::string MWIOUtils::splicePath(const std::string &path1, const std::string &path2)
{
    if (path1.size() <= 0) {
        return path1;
    }
    std::string newPath = path1;
    if (path1.at(path1.size() - 1) != '/') {
        newPath.append("/");
    }
    newPath.append(path2);
    
    return newPath;
}

MW_FRAMEWORK_END