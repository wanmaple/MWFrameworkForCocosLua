/******************************
 Description: Asset manager.
 Author: M.Wan
 Date: 6/13/2015
 ******************************/

#ifndef __UTILS_ASSET_MANAGER__
#define __UTILS_ASSET_MANAGER__

#include "../base/mwbase.h"
#include <string>
#include <vector>
#include <unordered_map>

MW_FRAMEWORK_BEGIN

class MWJsonObject;
class MWHttpDownloader;

MW_ENUM EAssetUpdateErrorType
{
    VERSION_IS_LATEST = 0,
    NO_SUCH_MODULE = 1,
    DOWNLOAD_FAILURE = 2,
};

class MW_INTERFACE IAssetUpdateDelegate
{
public:
    virtual ~IAssetUpdateDelegate() {}
    
    /**
     * Delegate when the version checking is over.
     */
    virtual void onVersionCheckCompleted(bool latest, int fileCount, bool needUpdateProgram, const std::string &programUpdateUrl) = 0;
    /**
     * Delegate when the version is updated.
     */
    virtual void onVersionUpdated() = 0;
    /**
     * Delegate when the module is updated.
     */
    virtual void onModuleUpdated(const std::string &moduleName) = 0;
    /**
     * Delegate when single file is updated.
     */
    virtual void onSingleFileUpdated(const std::string &moduleName, const std::string &filePath) = 0;
    /**
     * Delegate when the file is downloading.
     */
    virtual void onFileDownloading(const std::string &filePath, float progress) = 0;
};

class MW_DLL MWAssetManager
{
    MW_SINGLETON(MWAssetManager);
public:
    ~MWAssetManager();
    
    /**
     * Whether is the latest version.
     */
    bool isLatestVersion();
    /**
     * Update search path.
     */
    void configSearchPath();
    /**
     * File list from bundle/apk.
     */
    void setCopyFileList(const std::vector<std::string> &fileList);
    /**
     * Copy files from bundle/apk.
     */
    void copyFiles(const std::vector<std::string> &fileList);
    /**
     * Check version.
     */
    void checkVersion();
    /**
     * Check protocol file.
     */
    void checkProtocolFile();
    /**
     * Update version.
     */
    void updateVersion();
    /**
     * Check module.
     */
    int checkModule(const std::string &moduleName);
    /**
     * Update module.
     */
    void updateModule(const std::string &moduleName);
    /**
     * Write config into the file.
     */
    void flush();
    
    void setAssetRootUrl(const std::string &assetRootUrl);
    inline std::string getAssetRootPath()
    {
        return _assetRootUrl;
    }
    inline void setAssetUpdateDelegate(IAssetUpdateDelegate *delegate)
    {
        _delegate = delegate;
    }
    inline bool isDevelopMode()
    {
        return _isDevelopMode;
    }
    inline void setDevelopMode(bool isDevelopMode)
    {
        _isDevelopMode = isDevelopMode;
    }
    
    // Program version.
    MW_SYNTHESIZE(float, _programVersion, ProgramVersion);
    // Asset version.
    MW_SYNTHESIZE(float, _assetVersion, AssetVersion);
    // Local asset path.
    MW_SYNTHESIZE_PASS_BY_CONST_REF(std::string, _localAssetPath, LocalAssetPath);
    // Local asset version.
    MW_SYNTHESIZE_READONLY(float, _localVersion, LocalVersion);
    
private:
    enum DownloadFileType {
        BUNDLE_MD5_FILE = 0,
        VERSION_FILE = 1,
        CONFIG_FILE = 2,
        MODULE_FILE = 3,
        PROTOCOL_FILE = 4,
    };
    
    void clearSearchPath();
    void downloadBundleMd5File();
    void mergeMd5File();
    void downloadVersionFile();
    void downloadConfigFile();
    void downloadModuleFile();
    void downloadProtocolFile();
    void processAfterVersionFileDownload();
    void processAfterConfigFileDownload();
    void processAfterProtocolFileDownload();
    void checkMainModule();
    void processAfterSingleModleFileDownload(const std::string &moduleName);
    void saveVersion(float version);
    const char *fullLocalAssetPath(const std::string &filePath);
    void reportError(EAssetUpdateErrorType errorType , const std::string &errorMsg);
    void removeModuleFromUpdatingList(const std::string &moduleName);
    bool isFileUpdated(const std::string &filePath);
    
    bool _isDevelopMode;
    float _serverVersion;
    std::string _assetRootUrl;
    std::unordered_map<std::string, std::vector<std::string> > _downloadCache;
    std::vector<std::string> _updatingModuleList;
    bool _moduleUpdating;
    std::vector<std::string> _copyFileList;
    float _minProgramVersion;
    std::string _programUpdateUrl;
    MWJsonObject *_jsonConfig;
    MWJsonObject *_jsonBundleMd5;
    bool _globalMd5NeedFlush;
    MWHttpDownloader *_downloader;
    
    IAssetUpdateDelegate *_delegate;
};

MW_FRAMEWORK_END

#endif /* defined(__GameFramework__MWAssetManager__) */
