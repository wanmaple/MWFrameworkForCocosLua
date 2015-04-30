#if CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID

#include "MWIOUtils.h"

#include <sys/uio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <errno.h>
#include <vector>
#include <fstream>

using namespace std;

MW_FRAMEWORK_BEGIN

MWIOUtils::MWIOUtils()
{
}

string MWIOUtils::resourcePath(const std::string &path)
{
    return path;
}

bool MWIOUtils::fileExists(const std::string &path)
{
    string absolutePath = this->resourcePath(path);
    
    fstream file;
    file.open(absolutePath, ios::in);
    bool exist = false;
    if (file)
    {
        exist = true;
    }
    file.close();
    
    return exist;
}

bool MWIOUtils::directoryExists(const std::string &path)
{
    string absolutePath = this->resourcePath(path);
    
    struct stat info;
    
    if (::stat(absolutePath.c_str(), &info) != 0) {
        return false;
    } else if (info.st_mode & S_IFDIR) {
        return true;
    } else {
        return false;
    }
}

bool MWIOUtils::moveFile(const std::string &oldPath, const std::string &newPath)
{
    string oldAbsolutePath = this->resourcePath(oldPath);
    string newAbsolutePath = this->resourcePath(newPath);
    return rename(oldAbsolutePath.c_str(), newAbsolutePath.c_str()) == 0;
}

bool MWIOUtils::copyFile(const std::string &oldPath, const std::string &newPath)
{
    string oldAbsolutePath = this->resourcePath(oldPath);
    string newAbsolutePath = this->resourcePath(newPath);
    
    ifstream in;
    ofstream out;
    in.open(oldAbsolutePath, ios::in | ios::binary);		// open source file
    if (in.fail())
    {
        printf("Failed to open the source file.");
        in.close();
        out.close();
        return false;
    }
    out.open(newAbsolutePath, ios::out | ios::binary);
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

MWBinaryData *MWIOUtils::getDataFromFile(const std::string &filePath)
{
    string absolutePath = this->resourcePath(filePath);
    
    FILE *hFile = fopen(absolutePath.c_str(), "rb");
    fseek(hFile, 0, SEEK_END);
    MW_ULONG size = ftell(hFile);
    fseek(hFile, 0, SEEK_SET);
    
    MW_BYTE *pBuffer = (MW_BYTE *) malloc(size * sizeof(MW_BYTE));
    
    fread(pBuffer, sizeof(MW_BYTE), size, hFile);
    fclose(hFile);
    
    return MWBinaryData::create(pBuffer, size);
}

bool MWIOUtils::writeDataToFile(const MW_RAW_DATA content, MW_ULONG length, const std::string &filePath, bool isAppend)
{
    string absolutePath = this->resourcePath(filePath);
    
    ofstream ofs;
    auto mode = std::ios::out | std::ios::binary;
    if (isAppend) {
        mode |= std::ios::app;
    }
    ofs.open(absolutePath, mode);
    if (!ofs.is_open()) {
        return false;
    }
    
    ofs.write((const char *)content, length);
    ofs.close();
    
    return true;
}

bool MWIOUtils::removeFile(const std::string &filePath)
{
    string absolutePath = this->resourcePath(filePath);
    
    return remove(filePath.c_str()) == 0;
}

bool MWIOUtils::createFile(const std::string &filePath)
{
    string absolutePath = this->resourcePath(filePath);
    
    ofstream ofs;
    ofs.open(absolutePath);
    if (ofs.is_open()) {
        return true;
    }
    
    return false;
}

bool MWIOUtils::createDirectory(const std::string &directoryPath)
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