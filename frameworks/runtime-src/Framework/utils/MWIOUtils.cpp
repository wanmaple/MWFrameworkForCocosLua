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

bool MWIOUtils::fileExists(const std::string &path)
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

bool MWIOUtils::directoryExists(const std::string &path)
{
    struct stat info;
    
    if (::stat(path.c_str(), &info) != 0) {
        return false;
    } else if (info.st_mode & S_IFDIR) {
        return true;
    } else {
        return false;
    }
}

bool MWIOUtils::moveFile(const std::string &oldPath, const std::string &newPath)
{
    return rename(oldPath.c_str(), newPath.c_str()) == 0;
}

bool MWIOUtils::copyFile(const std::string &oldPath, const std::string &newPath)
{
    ifstream in;
    ofstream out;
    in.open(oldPath, ios::binary);		// open source file
    if (in.fail())
    {
        printf("Failed to open the source file.");
        in.close();
        out.close();
        return false;
    }
    out.open(newPath, ios::binary);
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

bool MWIOUtils::writeDataToFile(const unsigned char *content, unsigned long length, const std::string &filePath, bool isAppend)
{
    const char *mode = isAppend ? "ab" : "wb";
    FILE *hFile = fopen(filePath.c_str(), mode);
    if (!hFile)
    {
        return false;
    }
    
    size_t writtenSize = fwrite(content, length, 1, hFile);
    fclose(hFile);
    
    return writtenSize == length;
}

bool MWIOUtils::removeFile(const std::string &filePath)
{
    return remove(filePath.c_str()) == 0;
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
        if (::stat(dir, &st) == -1) {
            if (mkdir(dir, 0700)) {
                result = false;
                break;
            }
        }
        ++iter;
    }
    
    return result;
}

MW_FRAMEWORK_END