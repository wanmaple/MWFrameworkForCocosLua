/******************************
 Description: IO utils android strategy.
 Author: M.Wan
 Date: 8/18/2015
 ******************************/

#ifndef __PLATFORM_IOUTILS_STRATEGY_ANDROID__
#define __PLATFORM_IOUTILS_STRATEGY_ANDROID__

#include "../../base/mwbase.h"
#include "../IIOUtilsStrategy.h"
#include <string>

MW_FRAMEWORK_BEGIN

class MW_DLL MWIOUtilsStrategyAndroid : public IIOUtilsStrategy
{
public:
    std::string resourcePath(const std::string &path) override;
    bool fileExists(const std::string &path) override;
    bool moveFile(const std::string &oldPath, const std::string &newPath) override;
    bool copyFile(const std::string &oldPath, const std::string &newPath) override;
    MWBinaryData *getDataFromFile(const std::string &filePath) override;
    bool writeDataToFile(const MW_RAW_DATA content, MW_ULONG length, const std::string &filePath, bool isAppend) override;
    bool removeFile(const std::string &filePath) override;
    bool createFile(const std::string &filePath) override;
    bool createDirectory(const std::string &directoryPath) override;
};

MW_FRAMEWORK_END

#endif
