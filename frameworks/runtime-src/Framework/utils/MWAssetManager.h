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
#include <unordered_map>

MW_FRAMEWORK_BEGIN

class MWJsonObject;

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

class MW_DLL MWAssetManager : public IHttpDownloaderDelegate
{
    MW_SINGLETON(MWAssetManager);
public:
    ~MWAssetManager();
    
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
    
    MW_SYNTHESIZE(float, _localVersion, LocalVersion);
    MW_SYNTHESIZE(float, _programVersion, ProgramVersion);
    MW_SYNTHESIZE(float, _bundleResourceVersion, BundleResourceVersion);
    
private:
    void _configSearchPath();
    std::string _fullAssetPath(const std::string &path = "");
    
    bool _isDevelopMode;
    
    MWHttpDownloader * _downloader;
};

MW_FRAMEWORK_END

#endif /* defined(__GameFramework__MWAssetManager__) */
