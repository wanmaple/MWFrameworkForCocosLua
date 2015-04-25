/******************************
 Description: Zip format data.
 Author: M.Wan
 Date: 4/26/2015
 ******************************/

#ifndef __COMPRESSION_ZIP_DATA__
#define __COMPRESSION_ZIP_DATA__

#include "../base/mwbase.h"
#include <string>

MW_FRAMEWORK_BEGIN

/**
 * Zip wrapper.
 */
class MW_DLL MWZipData : public MWObject
{
public:
    MWZipData *createWithFile(const std::string &filePath, const std::string &password = "");
    
    virtual ~MWZipData();
    
    MWBinaryData *getCompressedFileData(const std::string &compressedFile);
    
protected:
    MWZipData();
    
    bool initWithFile(const std::string &filePath, const std::string &password);
    
    std::string _password;
    
};

MW_FRAMEWORK_END

#endif
