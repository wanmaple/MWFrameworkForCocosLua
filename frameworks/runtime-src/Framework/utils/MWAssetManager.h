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
    IO_ERROR,
    VERSION_CHECK_ERROR,
    NETWORK_ERROR,
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
     * Delegate when the single file is ready to download.
     */
    virtual void onAssetFileToDownload(const std::string &relativePath, double totalToDownload) = 0;
    /**
     * Delegate when the single file is downloading.
     */
    virtual void onAssetFileDownloading(const std::string &relativePath, double downloaded, double totalToDownload) = 0;
    /**
     * Delegate when the single file is updated.
     */
    virtual void onAssetFileDownloaded(const std::string &relativePath) = 0;
    /**
     * Delegate when the version is updated.
     */
    virtual void onVersionUpdated() = 0;
    /**
     * Delegate when download failed.
     */
    virtual void onUpdateError(EAssetUpdateErrorType errorType, const std::string &errorMsg) = 0;
};

class MW_DLL MWAssetManager : private IHttpDownloaderDelegate
{
    MW_SINGLETON(MWAssetManager);
public:
    ~MWAssetManager();
    
    void checkVersion();
    void beginUpdate();
    
    inline bool isDevelopMode()
    {
        return _isDevelopMode;
    }
    inline void setDevelopMode(bool isDevelopMode)
    {
        _isDevelopMode = isDevelopMode;
    }
    void setAssetUpdateDelegate(IAssetUpdateDelegate *delegate);
#if MW_ENABLE_SCRIPT_BINDING
    MW_SYNTHESIZE_RETAIN(cocos2d::Ref *, _scriptDelegate, ScriptDelegate);
#endif
    MW_SYNTHESIZE(int, _programVersion, ProgramVersion);
    MW_SYNTHESIZE_PASS_BY_CONST_REF(std::string, _bundleVersion, BundleVersion);
    MW_SYNTHESIZE_PASS_BY_CONST_REF(std::string, _assetRoot, AssetRootPath);
    MW_SYNTHESIZE_PASS_BY_CONST_REF(std::string, _serverUrl, ServerUrl);
    
private:
    // overrides
    virtual void onDownloadStarted(MWHttpDownloader *downloader, cocos2d::Ref *userdata);
    virtual void onDownloading(MWHttpDownloader *downloader, float progress, cocos2d::Ref *userdata);
    virtual void onDownloadCompleted(MWHttpDownloader *downloader, cocos2d::Ref *userdata);
    virtual void onDownloadFailed(MWHttpDownloader *downloader, const std::string &errorMsg, cocos2d::Ref *userdata);
    
    void _loadLocalVersion();
    void _configSearchPath();
    std::string _fullLocalAssetPath(const std::string &path = "");
    std::string _fullServerAssetPath(const std::string &path = "");
    void _mergeBundleMd5File();
    
    void _downloadVersionFile();
    void _processAfterDownloadVersionFile();
    void _downloadAssetConfigFile();
    void _processAfterDownloadAssetConfigFile();
    void _downloadBundleMd5File();
    void _processAfterDownloadBundleMd5File();
    void _downloadNextAssetFile();
    bool _saveVersion();
    
    void _delegateVersionCheckCompleted(bool latest, int fileCount, bool needUpdateProgram, const std::string &programUpdateUrl);
    void _delegateAssetFileToDownload(const std::string &relativePath, double totalToDownload);
    void _delegateAssetFileDownloading(const std::string &relativePath, double downloaded, double totalToDownload);
    void _delegateAssetFileDownloaded(const std::string &relativePath);
    void _delegateVersionUpdated();
    void _delegateUpdateError(EAssetUpdateErrorType errorType, const std::string &errorMsg);
    
    bool _isDevelopMode;
    bool _readyToUpdate;
    std::string _localVersion;
    std::string _newVersion;
    std::string _programUpdateUrl;
    std::queue<std::string> _downloadFileList;
    std::unordered_map<std::string, long> _fileSizeMap;
    
    MWHttpDownloader *_downloader;
    
    IAssetUpdateDelegate *_delegate;
};

MW_FRAMEWORK_END

#endif
