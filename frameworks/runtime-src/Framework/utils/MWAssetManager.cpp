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
#define AM_UPLOAD_RESOURCES_DIRECTORY "Asset"
#define AM_BUNDLE_MD5_FILE "bundle.md5.bin"
#define AM_ASSET_CONFIG_FILE "asset.config.bin"
#define AM_MAIN_MODULE_NAME "am.main"

// asset directorys
#define AM_ASSET_RESOURCE_DIRECTORY "res"
#define AM_ASSET_SCRIPT_DIRECTORY "src"

// version description file keys
#define AM_VERSION_KEY "version"
#define AM_MIN_PROGRAM_VERSION_KEY "min_cpp_version"
#define AM_PROGRAM_UPDATE_URL_KEY "cpp_update_url"

// config file keys
#define AM_FILE_COUNT_KEY "fileCount"
#define AM_TOTAL_SIZE_KEY "totalSize"
#define AM_MODULES_KEY "modules"
#define AM_FILE_LIST_KEY "files"

// userdefault keys
#define AM_USERDEFAULT_LOCAL_VERSION_KEY "am.local_version"

using namespace std;
using namespace cocos2d;

MW_FRAMEWORK_BEGIN

#define FLOAT_ACCURACY 0.001

MW_LOCAL bool IsFloatEqual(float num1, float num2)
{
    if (abs(num1 - num2) < FLOAT_ACCURACY) {
        return true;
    }
    return false;
}

MWAssetManager::MWAssetManager()
: _isDevelopMode(false)
, _localVersion()
, _programVersion()
, _assetRootUrl()
, _downloadFileType()
, _downloader(nullptr)
, _delegate(nullptr)
, _jsonAssetConfig(nullptr)
, _jsonVersion(nullptr)
, _downloadFileList()
, _versionLatest(false)
, _oldVersion()
{
    _downloader = new MWHttpDownloader();
    _downloader->setDelegate(this);
    
    _localVersion = UserDefault::getInstance()->getFloatForKey(AM_USERDEFAULT_LOCAL_VERSION_KEY);
}

MWAssetManager::~MWAssetManager()
{
    CC_SAFE_DELETE(_downloader);
    CC_SAFE_DELETE(_delegate);
    
    CC_SAFE_RELEASE(_jsonVersion);
    CC_SAFE_RELEASE(_jsonAssetConfig);
}

void MWAssetManager::checkVersion()
{
    if (_localVersion < _bundleResourceVersion) {
        _oldVersion = _localVersion;
        _localVersion = _bundleResourceVersion;
    }
    this->_configSearchPath();
    this->_downloadVersionFile();
}

void MWAssetManager::_downloadVersionFile()
{
    _downloadFileType = VERSION_FILE;
    
    string downloadPath = MWIOUtils::getInstance()->splicePath(_assetRootUrl, AM_VERSION_FILE);
    string savePath = MWIOUtils::getInstance()->splicePath(FileUtils::getInstance()->getWritablePath(), AM_VERSION_FILE);
    
    _downloader->beginDownloading(downloadPath, savePath);
}

void MWAssetManager::_processAfterDownloadVersionFile()
{
    string versionFilePath = MWIOUtils::getInstance()->splicePath(FileUtils::getInstance()->getWritablePath(), AM_VERSION_FILE);
    auto jsonVersion = MWJsonObject::createWithFile(versionFilePath);
    this->_setVersionJson(jsonVersion);
    
    if (!IsFloatEqual(jsonVersion->getNumber(AM_MIN_PROGRAM_VERSION_KEY), _programVersion) &&
        jsonVersion->getNumber(AM_MIN_PROGRAM_VERSION_KEY) > _programVersion) {
        if (_delegate) {
            _delegate->onVersionCheckCompleted(false, 0, true, jsonVersion->getString(AM_PROGRAM_UPDATE_URL_KEY));
        }
    } else if (!IsFloatEqual(jsonVersion->getNumber(AM_VERSION_KEY), _localVersion) &&
               jsonVersion->getNumber(AM_VERSION_KEY) > _localVersion) {
        this->_downloadBundleMd5File();
    } else {
        // already the latest.
        _versionLatest = true;
        this->_downloadBundleMd5File();
    }
}

void MWAssetManager::_downloadBundleMd5File()
{
    _downloadFileType = BUNDLE_MD5_FILE;
    
    string newVersion = _jsonVersion->getString(AM_VERSION_KEY);
    
    string downloadPath = MWIOUtils::getInstance()->splicePath(_assetRootUrl, AM_BUNDLE_MD5_DIRECTORY);
    downloadPath = MWIOUtils::getInstance()->splicePath(downloadPath, newVersion);
    downloadPath = MWIOUtils::getInstance()->splicePath(downloadPath, AM_BUNDLE_MD5_FILE);
    string savePath = MWIOUtils::getInstance()->splicePath(FileUtils::getInstance()->getWritablePath(), AM_BUNDLE_MD5_DIRECTORY);
    savePath = MWIOUtils::getInstance()->splicePath(savePath, newVersion);
    savePath = MWIOUtils::getInstance()->splicePath(savePath, AM_BUNDLE_MD5_FILE);
    
    _downloader->beginDownloading(downloadPath, savePath);
}

void MWAssetManager::_processAfterDownloadBundleMd5File()
{
    this->_mergeBundleMd5File();
    this->_downloadAssetConfigFile();
}

void MWAssetManager::_mergeBundleMd5File()
{
    // retreive new bundle md5 file.
    string newVersion = _jsonVersion->getString(AM_VERSION_KEY);
    
    string newBundleMd5Path = MWIOUtils::getInstance()->splicePath(FileUtils::getInstance()->getWritablePath(), AM_BUNDLE_MD5_DIRECTORY);
    newBundleMd5Path = MWIOUtils::getInstance()->splicePath(newBundleMd5Path, newVersion);
    newBundleMd5Path = MWIOUtils::getInstance()->splicePath(newBundleMd5Path, AM_BUNDLE_MD5_FILE);
    auto jsonNewBundleMd5 = MWJsonObject::createWithFile(newBundleMd5Path);
    
    // retreive old bundle md5 file.
    string oldVersion = __String::createWithFormat("%.2f", _oldVersion)->getCString();
    
    string oldBundleMd5Dir = MWIOUtils::getInstance()->splicePath(FileUtils::getInstance()->getWritablePath(), AM_BUNDLE_MD5_DIRECTORY);
    oldBundleMd5Dir = MWIOUtils::getInstance()->splicePath(oldBundleMd5Dir, oldVersion);
    string oldBundleMd5Path = MWIOUtils::getInstance()->splicePath(oldBundleMd5Dir, AM_BUNDLE_MD5_FILE);
    if (!MWIOUtils::getInstance()->fileExists(oldBundleMd5Path)) {
        // the first time.
        return;
    }
    auto jsonOldBundleMd5 = MWJsonObject::createWithFile(oldBundleMd5Path);
    
    // merge, delete unnecessary resources.
    _downloadFileList = queue<string>();
    auto oldKeys = jsonOldBundleMd5->allKeys();
    string filePath;
    for (const auto &key : oldKeys) {
        // should I also remove the modified resources?
        if (!jsonNewBundleMd5->hasKey(key)) {
            filePath = this->_fullLocalAssetPath(key);
            MWIOUtils::getInstance()->removeFile(filePath);
            
            _downloadFileList.push(key);
        } else if (jsonNewBundleMd5->getString(key) != jsonOldBundleMd5->getString(key)) {
            _downloadFileList.push(key);
        }
    }
}

void MWAssetManager::_downloadAssetConfigFile()
{
    _downloadFileType = ASSET_CONFIG_FILE;
    
    string downloadPath = MWIOUtils::getInstance()->splicePath(_assetRootUrl, AM_ASSET_CONFIG_FILE);
    string savePath = MWIOUtils::getInstance()->splicePath(FileUtils::getInstance()->getWritablePath(), AM_ASSET_CONFIG_FILE);
    
    _downloader->beginDownloading(downloadPath, savePath);
}

void MWAssetManager::_processAfterDownloadAssetConfigFile()
{
    string assetConfigFilePath = MWIOUtils::getInstance()->splicePath(FileUtils::getInstance()->getWritablePath(), AM_ASSET_CONFIG_FILE);
    auto jsonAssetConfig = MWJsonObject::createWithFile(assetConfigFilePath);
    this->_setAssetConfigJson(jsonAssetConfig);
    
    if (_delegate) {
        _delegate->onVersionCheckCompleted(_versionLatest, (int) _downloadFileList.size(), false, "");
    }
    
    if (!_versionLatest) {
        this->_downloadNextAssetFile();
    } else {
        this->_saveLatestVersion();
    }
}

void MWAssetManager::_downloadNextAssetFile()
{
    // todo. continue with the progress of last accident which cause the failure of the update.
    if (!_downloadFileList.empty()) {
        _downloadFileType = ASSET_FILE;
        
        string rpath = _downloadFileList.front();
        string downloadPath = this->_fullServerAssetPath(rpath);
        string savePath = this->_fullLocalAssetPath(rpath);
        
        _downloader->beginDownloading(downloadPath, savePath, __String::create(rpath), true);
    } else {
        this->_saveLatestVersion();
    }
}

void MWAssetManager::_saveLatestVersion()
{
    // remove old bundle md5 file.
    if (!_versionLatest) {
        string oldVersion = __String::createWithFormat("%.2f", _oldVersion)->getCString();
        
        string oldBundleMd5Dir = MWIOUtils::getInstance()->splicePath(FileUtils::getInstance()->getWritablePath(), AM_BUNDLE_MD5_DIRECTORY);
        oldBundleMd5Dir = MWIOUtils::getInstance()->splicePath(oldBundleMd5Dir, oldVersion);
        if (MWIOUtils::getInstance()->fileExists(oldBundleMd5Dir)) {
            MWIOUtils::getInstance()->removeFile(oldBundleMd5Dir);
        }
        
        _localVersion = _jsonVersion->getNumber(AM_VERSION_KEY);
        // save to user default.
        UserDefault::getInstance()->setFloatForKey(AM_USERDEFAULT_LOCAL_VERSION_KEY, _localVersion);
    }
    
    if (_delegate) {
        _delegate->onVersionUpdated();
    }
}

string MWAssetManager::_fullLocalAssetPath(const std::string &path)
{
    string assetDir = MWIOUtils::getInstance()->splicePath(FileUtils::getInstance()->getWritablePath(), AM_UPLOAD_RESOURCES_DIRECTORY);
    return MWIOUtils::getInstance()->splicePath(assetDir, path);
}

string MWAssetManager::_fullServerAssetPath(const std::string &path)
{
    string assetDir = MWIOUtils::getInstance()->splicePath(_assetRootUrl, AM_UPLOAD_RESOURCES_DIRECTORY);
    return MWIOUtils::getInstance()->splicePath(assetDir, path);
}

void MWAssetManager::_setVersionJson(mwframework::MWJsonObject *jsonVersion)
{
    CC_SAFE_RELEASE(_jsonVersion);
    _jsonVersion = jsonVersion;
    CC_SAFE_RETAIN(_jsonVersion);
}

void MWAssetManager::_setAssetConfigJson(mwframework::MWJsonObject *jsonAssetConfig)
{
    CC_SAFE_RELEASE(_jsonAssetConfig);
    _jsonAssetConfig = jsonAssetConfig;
    CC_SAFE_RETAIN(_jsonAssetConfig);
}

void MWAssetManager::_configSearchPath()
{
    vector<string> searchPaths = FileUtils::getInstance()->getSearchPaths();
    string assetPath = this->_fullLocalAssetPath();
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
        string resDir = this->_fullLocalAssetPath(AM_ASSET_RESOURCE_DIRECTORY);
        string srcDir = this->_fullLocalAssetPath(AM_ASSET_SCRIPT_DIRECTORY);
        searchPaths.push_back(resDir);
        searchPaths.push_back(srcDir);
        // set search order, the asset resource path should be the prepreerence.
        FileUtils::getInstance()->addSearchResolutionsOrder(resDir, true);
        FileUtils::getInstance()->addSearchResolutionsOrder(srcDir, true);
        FileUtils::getInstance()->addSearchResolutionsOrder(assetPath, true);
        
        // add lua script package path.
//#if MW_ENABLE_SCRIPT_BINDING
//        vector<string> packages;
//        packages.push_back(srcDir);
//        MWLuaUtils::getInstance()->addPackagePaths(packages);
//#endif
    }
}

void MWAssetManager::onDownloadStarted(mwframework::MWHttpDownloader *downloader, cocos2d::Ref *userdata)
{
    MW_UNUSED_PARAM(downloader);
    
    if (_downloadFileType == VERSION_FILE) {
        CCLOG("开始下载版本文件...");
    } else if (_downloadFileType == BUNDLE_MD5_FILE) {
        CCLOG("开始下载Bundle Md5文件...");
    } else if (_downloadFileType == ASSET_CONFIG_FILE) {
        CCLOG("开始下载Asset配置文件...");
    } else if (_downloadFileType == ASSET_FILE) {
        CCLOG("开始下载%s", static_cast<__String *>(userdata)->getCString());
    }
}

void MWAssetManager::onDownloading(mwframework::MWHttpDownloader *downloader, float progress, cocos2d::Ref *userdata)
{
    MW_UNUSED_PARAM(downloader);
    
    if (_downloadFileType == ASSET_FILE) {
        if (_delegate) {
            string rpath = static_cast<__String *>(userdata)->getCString();
            MWJsonArray * pFileInfo = _jsonAssetConfig->getJsonObject(AM_FILE_LIST_KEY)->getJsonArray(rpath);
            _delegate->onAssetFileDownloading(rpath, progress, (long) pFileInfo->getNumberAt(1));
        }
    }
}

void MWAssetManager::onDownloadCompleted(mwframework::MWHttpDownloader *downloader, cocos2d::Ref *userdata)
{
    MW_UNUSED_PARAM(downloader);
    MW_UNUSED_PARAM(userdata);
    
    if (_downloadFileType == VERSION_FILE) {
        CCLOG("版本文件下载完成。");
        this->_processAfterDownloadVersionFile();
    } else if (_downloadFileType == BUNDLE_MD5_FILE) {
        CCLOG("Bundle Md5文件下载完成。");
        this->_processAfterDownloadBundleMd5File();
    } else if (_downloadFileType == ASSET_CONFIG_FILE) {
        CCLOG("Asset配置文件下载完成。");
        this->_processAfterDownloadAssetConfigFile();
    } else if (_downloadFileType == ASSET_FILE) {
        string rpath = static_cast<__String *>(userdata)->getCString();
        CCLOG("%s下载完成。", rpath.c_str());
        if (_delegate) {
            _delegate->onAssetFileDownloaded(rpath);
        }
        this->_downloadNextAssetFile();
    }
}

void MWAssetManager::onDownloadFailed(mwframework::MWHttpDownloader *downloader, const std::string &errorMsg, cocos2d::Ref *userdata)
{
    MW_UNUSED_PARAM(downloader);
    
    CCLOG("下载错误: %s", errorMsg.c_str());
    
    if (_downloadFileType == VERSION_FILE) {
        CCLOG("版本文件下载失败...");
        if (_delegate) {
            _delegate->onUpdateError(EAssetUpdateErrorType::VERSION_CHECK_FAILURE, errorMsg);
        }
    } else if (_downloadFileType == BUNDLE_MD5_FILE) {
        CCLOG("Bundle Md5文件下载失败...");
        if (_delegate) {
            _delegate->onUpdateError(EAssetUpdateErrorType::VERSION_CHECK_FAILURE, errorMsg);
        }
    } else if (_downloadFileType == ASSET_CONFIG_FILE) {
        CCLOG("Asset配置文件下载失败...");
        if (_delegate) {
            _delegate->onUpdateError(EAssetUpdateErrorType::VERSION_CHECK_FAILURE, errorMsg);
        }
    }
}

MW_FRAMEWORK_END