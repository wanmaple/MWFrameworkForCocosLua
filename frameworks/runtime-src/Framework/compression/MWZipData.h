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
	 * @param password Zip password.
     */
    static MWZipData *createWithExistingFile(const std::string &filePath, const std::string &password = "");
    /**
     * Create an empty zip.
     *
     * @param filePath The zip file path to create.
	 * @param password Zip password.
     */
	static MWZipData *createWithNewFile(const std::string &filePath, const std::string &password = "");
	/**
	* Wrapper the zip data from raw data.
	*
	* @param rawData The zip file data.
	* @param password Zip password.
	*/
	static MWZipData *createWithBinaryData(MWBinaryData *rawData, const std::string &password = "");
    
    /**
     * ZipData destructor.
     */
    virtual ~MWZipData();
    
    /**
     * Prepare to unzip from the zip.
     * @note You have to call this before using "getCompressedFileData", otherwise you will failed to get the correct data.
     */
    void beginUnzip();
    /**
     * Stop to do unzip operations.
     * @note Don't forget to end after all unzip operations are done, otherwise you will failed to do other operations after that.
     */
    void endUnzip();
    /**
     * Prepare to zip new file to the zip.
     * @note You have to call this before using "zipNewFile", otherwise you will failed to add the data to the zip.
     */
    void beginZip();
    /**
     * Stop to do zip operations.
     * @note Don't forget to end after all zip operations are done, otherwise you will failed to do other operations after that.
     */
    void endZip();
    
    /**
     * Get the total raw data of the compressed file.
     *
     * @param compressedFile Compressed file path.
     * @password The compressed password if required.
     */
    MWBinaryData *getCompressedFileData(const std::string &compressedFile);
    
    /**
     * Compress new file into the zip.
     *
     * @param name The compressed file name.
     * @param fileData The data to compress.
     * @param Add a password if desired.
     * @param level Compressed level 0-9.
     */
    bool zipNewFile(const std::string &name, MWBinaryData *fileData, int level = 5);
    
protected:
    MWZipData();
    
    bool initWithExistingFile(const std::string &filePath, const std::string &password);
    bool initWithNewFile(const std::string &filePath, const std::string &password);
	bool initWithBinaryData(MWBinaryData *rawData, const std::string &password);
    
    std::string _filePath;
    std::string _password;
};

MW_FRAMEWORK_END

#endif
