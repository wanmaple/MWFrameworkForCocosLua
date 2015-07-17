/******************************
 Description: Asset manager.
 Author: M.Wan
 Date: 6/13/2015
 ******************************/

#ifndef __UTILS_ASSET_MANAGER__
#define __UTILS_ASSET_MANAGER__

#include "../base/mwbase.h"
#include "../net/http/MWHttpDownloader.h"
#include <string>
#include <vector>
#include <queue>
#include <unordered_map>

MW_FRAMEWORK_BEGIN

class MWJsonObject;

MW_ENUM EAssetUpdateErrorType
{
    VERSION_CHECK_FAILURE,
    FILE_UPDATE_FAILUTE,
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
     * Delegate when the single file is downloading.
     */
    virtual void onAssetFileDownloading(const std::string &filePath, float progress, long totalToDownload) = 0;
    /**
     * Delegate when the single file is updated.
     */
    virtual void onAssetFileDownloaded(const std::string &filePath) = 0;
    /**
     * Delegate when the version is updated.
     */
    virtual void onVersionUpdated() = 0;
    /**
     * Delegate when download failed.
     */
    virtual void onUpdateError(EAssetUpdateErrorType errorType, const std::string &errorMsg) = 0;
};

class MW_DLL MWAssetManager : public IHttpDownloaderDelegate
{
    MW_SINGLETON(MWAssetManager);
public:
    ~MWAssetManager();
    
    void checkVersion();
    
    // overrides
    virtual void onDownloadStarted(MWHttpDownloader *downloader, cocos2d::Ref *userdata);
    virtual void onDownloading(MWHttpDownloader *downloader, float progress, cocos2d::Ref *userdata);
    virtual void onDownloadCompleted(MWHttpDownloader *downloader, cocos2d::Ref *userdata);
    virtual void onDownloadFailed(MWHttpDownloader *downloader, const std::string &errorMsg, cocos2d::Ref *userdata);
    
    inline bool isDevelopMode()
    {
        return _isDevelopMode;
    }
    inline void setDevelopMode(bool isDevelopMode)
    {
        _isDevelopMode = isDevelopMode;
    }
    inline void setAssetUpdateDelegate(IAssetUpdateDelegate *delegate)
    {
        _delegate = delegate;
    }
    MW_SYNTHESIZE(float, _localVersion, LocalVersion);
    MW_SYNTHESIZE(float, _programVersion, ProgramVersion);
    MW_SYNTHESIZE(float, _bundleResourceVersion, BundleResourceVersion);
    MW_SYNTHESIZE_PASS_BY_CONST_REF(std::string, _assetRootUrl, AssetRootUrl);
    
private:
    enum EDownloadFileType {
        VERSION_FILE,
        BUNDLE_MD5_FILE,
        ASSET_CONFIG_FILE,
        ASSET_FILE,
    };
    
    void _configSearchPath();
    std::string _fullLocalAssetPath(const std::string &path = "");
    std::string _fullServerAssetPath(const std::string &path = "");
    void _setVersionJson(MWJsonObject *jsonVersion);
    void _setAssetConfigJson(MWJsonObject *jsonAssetConfig);
    void _mergeBundleMd5File();
    
    void _downloadVersionFile();
    void _processAfterDownloadVersionFile();
    void _downloadBundleMd5File();
    void _processAfterDownloadBundleMd5File();
    void _downloadAssetConfigFile();
    void _processAfterDownloadAssetConfigFile();
    void _downloadNextAssetFile();
    void _saveLatestVersion();
    
    bool _isDevelopMode;
    EDownloadFileType _downloadFileType;
    MWJsonObject *_jsonVersion;
    MWJsonObject *_jsonAssetConfig;
    std::queue<std::string> _downloadFileList;
    bool _versionLatest;
    float _oldVersion;
    
    MWHttpDownloader * _downloader;
    
    IAssetUpdateDelegate *_delegate;
};

MW_FRAMEWORK_END

#endif /* defined(__GameFramework__MWAssetManager__) */
