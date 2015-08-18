#if CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID

#include "MWIOUtilsStrategyAndroid.h"

#include <sys/uio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <errno.h>
#include <vector>
#include <fstream>

using namespace std;

MW_FRAMEWORK_BEGIN

string MWIOUtilsStrategyAndroid::resourcePath(const std::string &path)
{
    return path;
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

bool MWIOUtilsStrategyAndroid::createDirectory(const std::string &directoryPath)
{
    // split the directory path
    vector<string> dirPathArray;
    string subStr = directoryPath;
    do
    {
        auto pos = subStr.find_first_of('/');
        if (pos < subStr.size())
        {
            if (dirPathArray.size() > 0)
            {
                dirPathArray.push_back(dirPathArray[dirPathArray.size() - 1] + string("/") + subStr.substr(0, pos));
            }
            else
            {
                dirPathArray.push_back(subStr.substr(0, pos));
            }
            subStr = subStr.substr(pos + 1);
            continue;
        }
        dirPathArray.push_back(directoryPath);
        break;
    } while (true);
    
    // create directory in a loop.
    bool result = true;
    auto iter = dirPathArray.begin();
    while (iter != dirPathArray.end())
    {
        auto dir = (*iter).c_str();
        struct stat st = {0};
        if (::stat(this->resourcePath(dir).c_str(), &st) == -1) {
            if (mkdir(this->resourcePath(dir).c_str(), 0700)) {
                result = false;
                break;
            }
        }
        ++iter;
    }
    
    return result;
}

MW_FRAMEWORK_END

#endif