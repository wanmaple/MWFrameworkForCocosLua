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
    /**
     * Wrapper the zip data from the file and password if required.
     *
     * @param filePath The zip file path.
     */
    static MWZipData *createWithExistingFile(const std::string &filePath);
    /**
     * Create an empty zip.
     *
     * @param filePath The zip file path to create.
     */
    static MWZipData *createWithNewFile(const std::string &filePath);
    
    /**
     * ZipData destructor.
     */
    virtual ~MWZipData();
    
    void beginUnzip();
    void endUnzip();
    
    void beginZip();
    void endZip();
    
    /**
     * Get the total raw data of the compressed file.
     *
     * @param compressedFile Compressed file path.
     * @password The compressed password if required.
     */
    MWBinaryData *getCompressedFileData(const std::string &compressedFile, const std::string &password = "");
    
    /**
     * Compress new file into the zip.
     *
     * @param name The compressed file name.
     * @param fileData The data to compress.
     * @param Add a password if desired.
     * @param level Compressed level 0-9.
     */
    bool zipNewFile(const std::string &name, MWBinaryData *fileData, const std::string &password = "", int level = 5);
    
protected:
    MWZipData();
    
    bool initWithExistingFile(const std::string &filePath);
    bool initWithNewFile(const std::string &filePath);
    
    std::string _filePath;
    
};

MW_FRAMEWORK_END

#endif
