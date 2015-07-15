#include "MWAssetManager.h"
#include "../json/MWJsonStructure.h"
#include "../platform/MWIOUtils.h"
#include "../net/http/MWHttpDownloader.h"
#include "../lua/MWLuaUtils.h"
#include "cocos2d.h"

#include <vector>

// asset manager related
#define AM_VERSION_FILE "version.bin"
#define AM_BUNDLE_MD5_DIRECTORY "BundleMd5"
#define AM_UPLOAD_DIRECTORY "Upload"
#define AM_UPLOAD_RESOURCES_DIRECTORY "Resources"
#define AM_BUNDLE_MD5_FILE "bundle.md5.bin"
#define AM_ASSET_CONFIG_FILE "asset.config.bin"
#define AM_MAIN_MODULE_NAME "am.main"

// asset directorys
#define AM_ASSET_RESOURCE_DIRECTORY "resources"
#define AM_ASSET_SCRIPT_DIRECTORY "scripts"

// version description file keys
#define AM_VERSION_KEY "version"
#define AM_MIN_PROGRAM_VERSION_KEY "min_cpp_version"
#define AM_PROGRAM_UPDATE_URL_KEY "cpp_update_url"

// userdefault keys
#define AM_USERDEFAULT_LOCAL_VERSION_KEY "am.local_version"
#define AM_USERDEFAULT_PROGRAM_VERSION_KEY "am.program_version"

using namespace std;
using namespace cocos2d;

MW_FRAMEWORK_BEGIN

MWAssetManager::MWAssetManager()
: _isDevelopMode(false)
, _localVersion()
, _programVersion()
, _downloader(nullptr)
{
    _downloader = new MWHttpDownloader();
    _downloader->setDelegate(this);
    
    _localVersion = UserDefault::getInstance()->getFloatForKey(AM_USERDEFAULT_LOCAL_VERSION_KEY);
}

MWAssetManager::~MWAssetManager()
{
    CC_SAFE_DELETE(_downloader);
}

string MWAssetManager::_fullAssetPath(const std::string &path)
{
    string assetDir = MWIOUtils::getInstance()->splicePath(FileUtils::getInstance()->getWritablePath(), AM_UPLOAD_RESOURCES_DIRECTORY);
    return MWIOUtils::getInstance()->splicePath(assetDir, path);
}

void MWAssetManager::_configSearchPath()
{
    vector<string> searchPaths = FileUtils::getInstance()->getSearchPaths();
    string assetPath = this->_fullAssetPath();
    // check whether the asset resource path is already set.
    bool didSet = false;
    for (const auto &path : searchPaths) {
        if (path == assetPath) {
            didSet = true;
            break;
        }
    }
    // set if non-exist.
    if (!didSet) {
        searchPaths.push_back(assetPath);
        string resDir = this->_fullAssetPath(AM_ASSET_RESOURCE_DIRECTORY);
        string srcDir = this->_fullAssetPath(AM_ASSET_SCRIPT_DIRECTORY);
        searchPaths.push_back(resDir);
        searchPaths.push_back(srcDir);
        // set search order, the asset resource path should be the prepreerence.
        FileUtils::getInstance()->addSearchResolutionsOrder(resDir, true);
        FileUtils::getInstance()->addSearchResolutionsOrder(srcDir, true);
        FileUtils::getInstance()->addSearchResolutionsOrder(assetPath, true);
        
        // add lua script package path.
#if MW_ENABLE_SCRIPT_BINDING
        vector<string> packages;
        packages.push_back(srcDir);
        MWLuaUtils::getInstance()->addPackagePaths(packages);
#endif
    }
}

void MWAssetManager::onDownloadStarted(mwframework::MWHttpDownloader *downloader, cocos2d::Ref *userdata)
{
    MW_UNUSED_PARAM(downloader);
}

void MWAssetManager::onDownloading(mwframework::MWHttpDownloader *downloader, float progress, cocos2d::Ref *userdata)
{
    MW_UNUSED_PARAM(downloader);
    MW_UNUSED_PARAM(progress);
    MW_UNUSED_PARAM(userdata);
}

void MWAssetManager::onDownloadCompleted(mwframework::MWHttpDownloader *downloader, cocos2d::Ref *userdata)
{
    MW_UNUSED_PARAM(downloader);
    MW_UNUSED_PARAM(userdata);
}

void MWAssetManager::onDownloadFailed(mwframework::MWHttpDownloader *downloader, const std::string &errorMsg, cocos2d::Ref *userdata)
{
    MW_UNUSED_PARAM(downloader);
    
    CCLOG("Download file error: %s", errorMsg.c_str());
}

MW_FRAMEWORK_END