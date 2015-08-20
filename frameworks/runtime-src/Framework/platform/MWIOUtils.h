/******************************
 Description: Handle IO operations
 Author: M.Wan
 Date: 3/18/2015
 ******************************/

#ifndef __UTILS_IOUTILS__
#define __UTILS_IOUTILS__

#include "../base/mwbase.h"
#include "cocos2d.h"
#include <string>

MW_FRAMEWORK_BEGIN

class MWIOUtilsStrategy;

/**
 * A helper class to handle io operations.
 */
class MW_DLL MWIOUtils
{
    /**
     * IOUtils is a singleton.
     */
    MW_SINGLETON(MWIOUtils);
public:
    ~MWIOUtils();
    
    /**
     * Get the absolute path to the relative resource path.
     *
     * @param path Relative path to the resource folder.
     *
     * @return The absolute path.
     */
    std::string resourcePath(const std::string &path);
    
    /**
     * Check whether the specified file does exist.
     *
     * @param path File path to check.
     *
     * @return A boolean value.
     */
    bool fileExists(const std::string &path);
    
    /**
     * Move file from old path to new path.
     *
     * @param oldPath Source file path.
     * @param newPath New file path.
     *
     * @return Operation result.
     */
    bool moveFile(const std::string &oldPath, const std::string &newPath);
    
    /**
     * Copy file from old path to new path.
     *
     * @param oldPath Source file path.
     * @param newPath New file path.
     *
     * @return Operation result.
     */
    bool copyFile(const std::string &oldPath, const std::string &newPath);
    
    /**
     * Get the raw data from the specified file.
     *
     * @param filePath Source file path.
     *
     * @return The raw data of the specified file, or nullptr if it failed to read.
     */
    MWBinaryData *getDataFromFile(const std::string &filePath);
    
    /**
     * Write content to the specified file.
     *
     * @param content File content to write.
     * @param length Content size.
     * @param filePath Destination file path.
     * @param isAppend Whether to append the content at the end of the file.
     * @return Operation result.
     */
    bool writeDataToFile(const MW_RAW_DATA content, MW_ULONG length, const std::string &filePath, bool isAppend = false);
    bool writeDataToFile(MWBinaryData *data, const std::string &filePath, bool isAppend = false);
    
    /**
     * Remove the specified file.
     *
     * @param filePath Destination file path.
     *
     * @return Operation result.
     */
    bool removeFile(const std::string &filePath);
    
    /**
     * Create a new file.
     *
     * @param filePath The new file path.
     *
     * @return Operation result.
     */
    bool createFile(const std::string &filePath);
    
    /**
     * Create a new directory.
     *
     * @param directoryPath The new directory path.
     *
     * @return Operation result.
     */
    bool createDirectory(const std::string &directoryPath);
    
    std::string splicePath(const std::string &path1, const std::string &path2);
    
protected:
    MWIOUtilsStrategy *_strategy;
};

MW_FRAMEWORK_END

#endif