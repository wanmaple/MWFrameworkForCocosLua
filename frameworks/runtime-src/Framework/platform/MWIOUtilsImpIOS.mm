#if CC_TARGET_PLATFORM == CC_PLATFORM_IOS

#include "MWIOUtils.h"

#include <sys/uio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <errno.h>
#include <vector>
#include <fstream>

#import <Foundation/Foundation.h>
#import <UIKit/UIKit.h>

using namespace std;

MW_FRAMEWORK_BEGIN

MWIOUtils::MWIOUtils()
{
}

string MWIOUtils::resourcePath(const std::string &path)
{
    NSString *fname = [NSString stringWithCString:path.c_str() encoding:NSUTF8StringEncoding];
    NSString *absolutePath = [[[NSBundle mainBundle] resourcePath] stringByAppendingPathComponent:fname];
    
    return string([absolutePath cStringUsingEncoding:NSUTF8StringEncoding]);
}

bool MWIOUtils::fileExists(const std::string &path)
{
    string absolutePath = this->resourcePath(path);
    
    BOOL isDirectory = NO;
    BOOL result = [[NSFileManager defaultManager] fileExistsAtPath:[NSString stringWithCString:absolutePath.c_str() encoding:NSUTF8StringEncoding] isDirectory:&isDirectory];
    
    return result && !isDirectory;
}

bool MWIOUtils::moveFile(const std::string &oldPath, const std::string &newPath)
{
    string oldAbsolutePath = this->resourcePath(oldPath);
    string newAbsolutePath = this->resourcePath(newPath);
    
    return [[NSFileManager defaultManager] moveItemAtPath:[NSString stringWithCString:oldAbsolutePath.c_str() encoding:NSUTF8StringEncoding] toPath:[NSString stringWithCString:newAbsolutePath.c_str() encoding:NSUTF8StringEncoding] error:nil];
}

bool MWIOUtils::copyFile(const std::string &oldPath, const std::string &newPath)
{
    string oldAbsolutePath = this->resourcePath(oldPath);
    string newAbsolutePath = this->resourcePath(newPath);
    
    return [[NSFileManager defaultManager] copyItemAtPath:[NSString stringWithCString:oldAbsolutePath.c_str() encoding:NSUTF8StringEncoding] toPath:[NSString stringWithCString:newAbsolutePath.c_str() encoding:NSUTF8StringEncoding] error:nil];
}

MWBinaryData *MWIOUtils::getDataFromFile(const std::string &filePath)
{
    string absolutePath = this->resourcePath(filePath);
    
    FILE *hFile = fopen(absolutePath.c_str(), "rb");
    if (!hFile) {
        return nullptr;
    }
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
    
    if (this->fileExists(absolutePath)) {
        return [[NSFileManager defaultManager] removeItemAtPath:[NSString stringWithCString:absolutePath.c_str() encoding:NSUTF8StringEncoding] error:nil];
    }
    
    return false;
}

bool MWIOUtils::createFile(const std::string &filePath)
{
    string absolutePath = this->resourcePath(filePath);
    
    return [[NSFileManager defaultManager] createFileAtPath:[NSString stringWithCString:absolutePath.c_str() encoding:NSUTF8StringEncoding] contents:nil attributes:nil];
}

bool MWIOUtils::createDirectory(const std::string &directoryPath)
{
    string absolutePath = this->resourcePath(directoryPath);
    
    return [[NSFileManager defaultManager] createDirectoryAtPath:[NSString stringWithCString:absolutePath.c_str() encoding:NSUTF8StringEncoding] withIntermediateDirectories:YES attributes:nil error:nil];
}

MW_FRAMEWORK_END

#endif