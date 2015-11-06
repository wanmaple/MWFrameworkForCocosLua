#if CC_TARGET_PLATFORM == CC_PLATFORM_WIN32

#include "MWIOUtilsStrategyWin32.h"

#include <windows.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <direct.h>
#include <errno.h>
#include <vector>
#include <fstream>

#include "cocos2d.h"

using namespace std;
using namespace cocos2d;

MW_FRAMEWORK_BEGIN

string MWIOUtilsStrategyWin32::resourcePath(const std::string &path)
{
	char executablePath[1024] = { 0 };
	DWORD charsCopied = GetModuleFileNameA(nullptr, executablePath, 1024);
	if (charsCopied > 0 && charsCopied < 1024)
	{
		return string(executablePath) + "\\..\\" + path;
	}
	else 
	{
		return FileUtils::getInstance()->fullPathForFilename(path);
	}
}

bool MWIOUtilsStrategyWin32::fileExists(const std::string &path)
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

bool MWIOUtilsStrategyWin32::moveFile(const std::string &oldPath, const std::string &newPath)
{
    return rename(oldPath.c_str(), newPath.c_str()) == 0;
}

bool MWIOUtilsStrategyWin32::copyFile(const std::string &oldPath, const std::string &newPath)
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

MWBinaryData *MWIOUtilsStrategyWin32::getDataFromFile(const std::string &filePath)
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

bool MWIOUtilsStrategyWin32::writeDataToFile(const MW_RAW_DATA content, MW_ULONG length, const std::string &filePath, bool isAppend)
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

bool MWIOUtilsStrategyWin32::removeFile(const std::string &filePath)
{
    return remove(filePath.c_str()) == 0;
}

bool MWIOUtilsStrategyWin32::createFile(const std::string &filePath)
{
    ofstream ofs;
    ofs.open(filePath);
    if (ofs.is_open()) {
        return true;
    }
    
    return false;
}

bool MWIOUtilsStrategyWin32::createDirectory(const std::string &path)
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

	bool success = true;
	for (const auto &path : dirs)
	{
		if (::_mkdir(path.c_str()))
		{
			success = false;
			break;
		}
	}

	return success;
}

MW_FRAMEWORK_END

#endif