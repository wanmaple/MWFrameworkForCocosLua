#if CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID

#include "MWIOUtilsStrategyAndroid.h"

#include <sys/uio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <errno.h>
#include <dirent.h>
#include <vector>
#include <fstream>

#include "cocos2d.h"

using namespace std;
using namespace cocos2d;

MW_FRAMEWORK_BEGIN

string MWIOUtilsStrategyAndroid::resourcePath(const std::string &path)
{
    // no way to retrieve absolute path while the assets is a zip file.
    return FileUtils::getInstance()->fullPathForFilename(path);
}

bool MWIOUtilsStrategyAndroid::fileExists(const std::string &path)
{
    fstream file;
    file.open(path, ios::in);
    bool exist = false;
    if (file)
    {
        exist = true;
    }
    file.close();
    
    return exist;
}

bool MWIOUtilsStrategyAndroid::moveFile(const std::string &oldPath, const std::string &newPath)
{
    return rename(oldPath.c_str(), newPath.c_str()) == 0;
}

bool MWIOUtilsStrategyAndroid::copyFile(const std::string &oldPath, const std::string &newPath)
{
    ifstream in;
    ofstream out;
    in.open(oldPath, ios::in | ios::binary);		// open source file
    if (in.fail())
    {
        printf("Failed to open the source file.");
        in.close();
        out.close();
        return false;
    }
    out.open(newPath, ios::out | ios::binary);
    if (out.fail())
    {
        printf("Failed to create the target file.");
        out.close();
        in.close();
        return false;
    }
    out << in.rdbuf();
    out.close();
    in.close();
    return true;
}

MWBinaryData *MWIOUtilsStrategyAndroid::getDataFromFile(const std::string &filePath)
{
    FILE *hFile = fopen(filePath.c_str(), "rb");
    fseek(hFile, 0, SEEK_END);
    MW_ULONG size = ftell(hFile);
    fseek(hFile, 0, SEEK_SET);
    
    MW_BYTE *pBuffer = (MW_BYTE *) malloc(size * sizeof(MW_BYTE));
    
    fread(pBuffer, sizeof(MW_BYTE), size, hFile);
    fclose(hFile);
    
    return MWBinaryData::create(pBuffer, size);
}

bool MWIOUtilsStrategyAndroid::writeDataToFile(const MW_RAW_DATA content, MW_ULONG length, const std::string &filePath, bool isAppend)
{
    ofstream ofs;
    auto mode = std::ios::out | std::ios::binary;
    if (isAppend) {
        mode |= std::ios::app;
    }
    ofs.open(filePath, mode);
    if (!ofs.is_open()) {
        return false;
    }
    
    ofs.write((const char *)content, length);
    ofs.close();
    
    return true;
}

bool MWIOUtilsStrategyAndroid::removeFile(const std::string &filePath)
{
    return remove(filePath.c_str()) == 0;
}

bool MWIOUtilsStrategyAndroid::createFile(const std::string &filePath)
{
    ofstream ofs;
    ofs.open(filePath);
    if (ofs.is_open()) {
        return true;
    }
    
    return false;
}

bool MWIOUtilsStrategyAndroid::createDirectory(const std::string &path)
{
    // Split the path
    size_t start = 0;
    size_t found = path.find_first_of("/\\", start);
    std::string subpath;
    std::vector<std::string> dirs;
    
    if (found != std::string::npos)
    {
        while (true)
        {
            subpath = path.substr(start, found - start + 1);
            if (!subpath.empty())
                dirs.push_back(subpath);
            start = found + 1;
            found = path.find_first_of("/\\", start);
            if (found == std::string::npos)
            {
                if (start < path.length())
                {
                    dirs.push_back(path.substr(start));
                }
                break;
            }
        }
    }

    DIR *dir = NULL;

    // Create path recursively
    subpath = "";
    for (int i = 0; i < dirs.size(); ++i)
    {
        subpath += dirs[i];
        dir = opendir(subpath.c_str());
        
        if (!dir)
        {
            // directory doesn't exist, should create a new one
            
            int ret = mkdir(subpath.c_str(), S_IRWXU | S_IRWXG | S_IRWXO);
            if (ret != 0 && (errno != EEXIST))
            {
                // current directory can not be created, sub directories can not be created too
                // should return
                return false;
            }
        }
        else
        {
            // directory exists, should close opened dir
            closedir(dir);
        }
    }

    return true;
}

MW_FRAMEWORK_END

#endif