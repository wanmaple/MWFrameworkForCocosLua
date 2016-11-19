/******************************
 Description: IO utils strategy base.
 Author: M.Wan
 Date: 3/18/2015
 ******************************/

#ifndef __PLATFORM_IOUTILS_STRATEGY__
#define __PLATFORM_IOUTILS_STRATEGY__

#include "../base/mwbase.h"
#include <string>

MW_FRAMEWORK_BEGIN

class MW_INTERFACE IIOUtilsStrategy
{
public:
    virtual ~IIOUtilsStrategy() {}
    
    virtual std::string resourcePath(const std::string &path) = 0;
    virtual bool fileExists(const std::string &path) = 0;
    virtual bool moveFile(const std::string &oldPath, const std::string &newPath) = 0;
    virtual bool copyFile(const std::string &oldPath, const std::string &newPath) = 0;
    virtual MWBinaryData *getDataFromFile(const std::string &filePath) = 0;
    virtual bool writeDataToFile(const MW_RAW_DATA content, MW_ULONG length, const std::string &filePath, bool isAppend) = 0;
    virtual bool removeFile(const std::string &filePath) = 0;
    virtual bool createFile(const std::string &filePath) = 0;
    virtual bool createDirectory(const std::string &directoryPath) = 0;
};

MW_FRAMEWORK_END

#endif
