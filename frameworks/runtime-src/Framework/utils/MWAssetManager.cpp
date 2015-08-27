#include "MWAssetManager.h"

#include "../json/MWJsonStructure.h"
#include "../platform/MWIOUtils.h"
#include "../net/http/MWHttpDownloader.h"
#include "../lua/MWLuaUtils.h"
#include "cocos2d.h"

#include <vector>

// files and directorys
#define AM_VERSION_FILE "version.json"
#define AM_CONFIG_FILE "config.json"
#define AM_BUNDLE_MD5_FILE "bundle_md5.json"
#define AM_LOCAL_VERSION_FILE "local_version.json"
#define AM_LOCAL_MD5_FILE "local_md5.json"
#define AM_ASSET_DIR "Asset"
#define AM_BUNDLE_MD5_DIR "BundleMd5"
#define AM_SCRIPT_DIR "src"

// version description file keys
#define AM_VERSION_STR_KEY "version_str"
#define AM_CPP_VERSION_KEY "cpp_version"
#define AM_UPDATE_URL_KEY "cpp_update_url"
#define AM_FILE_COUNT_KEY "file_count"
#define AM_FILE_INFO_KEY "file_info"

// file id to identify what kinds of file is downloading or downloaded.
#define AM_VERSION_FILE_ID "am.version.id"
#define AM_CONFIG_FILE_ID "am.config.id"
#define AM_BUNDLE_MD5_FILE_ID "am.bundle.md5.id"

using namespace std;
using namespace cocos2d;

MW_FRAMEWORK_BEGIN

MWAssetManager::MWAssetManager()
: _isDevelopMode(false)
, _bundleVersion()
, _programVersion(0)
, _serverUrl()
, _assetRoot()
, _delegate(nullptr)
, _downloader(nullptr)
, _downloadFileList()
, _fileSizeMap()
, _readyToUpdate(false)
, _localVersion()
, _newVersion()
, _programUpdateUrl()
{
    _downloader = new MWHttpDownloader();
    _downloader->setDelegate(this);
}

MWAssetManager::~MWAssetManager()
{
    CC_SAFE_DELETE(_downloader);
    CC_SAFE_DELETE(_delegate);
}

void MWAssetManager::checkVersion()
{
    this->_loadLocalVersion();
    this->_configSearchPath();
    this->_downloadVersionFile();
}

void MWAssetManager::beginUpdate()
{
    if (!_readyToUpdate) {
        CCLOG("Unable to update, did you call the checkVersion first?");
        return;
    }
    this->_downloadNextAssetFile();
}

void MWAssetManager::setAssetUpdateDelegate(mwframework::IAssetUpdateDelegate *delegate)
{
    CC_SAFE_DELETE(_delegate);
    _delegate = delegate;
}

void MWAssetManager::_loadLocalVersion()
{
    if (!MWIOUtils::getInstance()->directoryExists(this->_fullLocalAssetPath())) {
        MWIOUtils::getInstance()->createDirectory(this->_fullLocalAssetPath());
    }
    string assetDir = this->_fullLocalAssetPath();
    string localVersionPath = MWIOUtils::getInstance()->splicePath(assetDir, AM_LOCAL_VERSION_FILE);
    if (!MWIOUtils::getInstance()->fileExists(localVersionPath)) {
        _localVersion = _bundleVersion;
    } else {
        MWJsonObject *localVersionJson = MWJsonObject::createWithFile(localVersionPath);
        if (!localVersionJson || !localVersionJson->hasKey(AM_VERSION_STR_KEY) || !localVersionJson->hasKey(AM_CPP_VERSION_KEY)) {
            // local version file is damaged. delete it.
            MWIOUtils::getInstance()->removeFile(localVersionPath);
            _localVersion = _bundleVersion;
        } else {
            // check whether cpp version is the latest
            int cppVersion = (int) localVersionJson->getNumber(AM_CPP_VERSION_KEY);
            if (cppVersion < _programVersion) {
                // remove all updated data.
                MWIOUtils::getInstance->removeDirectory(this->_fullLocalAssetPath());
                _localVersion = _bundleVersion;
            } else {
                _localVersion = localVersionJson->getString(AM_VERSION_STR_KEY);
            }
        }
    }
}

void MWAssetManager::_downloadVersionFile()
{
    string url = this->_fullServerAssetPath(AM_VERSION_FILE);
    string savePath = this->_fullLocalAssetPath(AM_VERSION_FILE);
    
    _downloader->beginDownloading(url, savePath, __String::create(AM_VERSION_FILE_ID));
}

void MWAssetManager::_processAfterDownloadVersionFile()
{
    string versionFilePath = this->_fullLocalAssetPath(AM_VERSION_FILE);
    auto versionJson = MWJsonObject::createWithFile(versionFilePath);
    if (!versionJson) {
        this->_delegateUpdateError(EAssetUpdateErrorType::VERSION_CHECK_ERROR, "Failed to parse version file.");
        return;
    }
    if (!versionJson->hasKey(AM_VERSION_STR_KEY) || !versionJson->hasKey(AM_UPDATE_URL_KEY)) {
        this->_delegateUpdateError(EAssetUpdateErrorType::VERSION_CHECK_ERROR, "Invalid version file.");
        return;
    }
    _newVersion = versionJson->getString(AM_VERSION_STR_KEY);
    _programUpdateUrl = versionJson->getString(AM_UPDATE_URL_KEY);
    
    if (_localVersion == _newVersion) {
        // download related md5 file
        string url = this->_fullServerAssetPath(string(AM_BUNDLE_MD5_DIR) + "/" + _newVersion + "/" + AM_BUNDLE_MD5_FILE);
        string savePath = this->_fullLocalAssetPath(AM_LOCAL_MD5_FILE);
        
        _downloader->beginDownloading(url, savePath, __String::create(AM_BUNDLE_MD5_FILE_ID));
    } else {
        this->_downloadAssetConfigFile();
    }
}

void MWAssetManager::_downloadAssetConfigFile()
{
    string url = this->_fullServerAssetPath(AM_CONFIG_FILE);
    string savePath = this->_fullLocalAssetPath(AM_CONFIG_FILE);
    
    _downloader->beginDownloading(url, savePath, __String::create(AM_CONFIG_FILE_ID));
}

void MWAssetManager::_processAfterDownloadAssetConfigFile()
{
    string configFilePath = this->_fullLocalAssetPath(AM_CONFIG_FILE);
    auto configJson = MWJsonObject::createWithFile(configFilePath);
    if (!configJson) {
        this->_delegateUpdateError(EAssetUpdateErrorType::VERSION_CHECK_ERROR, "Failed to parse config file.");
        return;
    }
    if (!configJson->hasKey(AM_FILE_COUNT_KEY) || !configJson->hasKey(AM_FILE_INFO_KEY)) {
        this->_delegateUpdateError(EAssetUpdateErrorType::VERSION_CHECK_ERROR, "Invalid config file.");
        return;
    }
    MWJsonObject *fileInfoJson = configJson->getJsonObject(AM_FILE_INFO_KEY);
    if (!fileInfoJson) {
        this->_delegateUpdateError(EAssetUpdateErrorType::VERSION_CHECK_ERROR, "Invalid config file.");
        return;
    }
    _fileSizeMap.clear();
    auto allKeys = fileInfoJson->allKeys();
    for (const auto &key : allKeys) {
        _fileSizeMap[key] = (long) fileInfoJson->getNumber(key);
    }
    
    this->_downloadBundleMd5File();
}

void MWAssetManager::_downloadBundleMd5File()
{
    string url = this->_fullServerAssetPath(string(AM_BUNDLE_MD5_DIR) + "/" + _newVersion + "/" + AM_BUNDLE_MD5_FILE);
    string savePath = this->_fullLocalAssetPath(AM_BUNDLE_MD5_FILE);
    
    _downloader->beginDownloading(url, savePath, __String::create(AM_BUNDLE_MD5_FILE_ID));
}

void MWAssetManager::_processAfterDownloadBundleMd5File()
{
    this->_mergeBundleMd5File();
    _readyToUpdate = true;
    this->_delegateVersionCheckCompleted(false, (int) _downloadFileList.size(), !_programUpdateUrl.empty(), _programUpdateUrl);
}

void MWAssetManager::_mergeBundleMd5File()
{
    // retreive new bundle md5 file.
    string bundleMd5Path = this->_fullLocalAssetPath(AM_BUNDLE_MD5_FILE);
    MWJsonObject *bundleMd5Json = MWJsonObject::createWithFile(bundleMd5Path);
    if (!bundleMd5Json) {
        this->_delegateUpdateError(EAssetUpdateErrorType::VERSION_CHECK_ERROR, "Failed to parse bundle md5 file.");
        return;
    }
    // retreive local bundle md5 file.
    string localMd5Path = this->_fullLocalAssetPath(AM_LOCAL_MD5_FILE);
    MWJsonObject *localMd5Map = MWJsonObject::create();
    if (MWIOUtils::getInstance()->fileExists(localMd5Path)) {
        MWJsonObject *localMd5Json = MWJsonObject::createWithFile(localMd5Path);
        if (!localMd5Json) {
            // invalid local md5 file, delete it.
            MWIOUtils::getInstance()->removeFile(localMd5Path);
        } else {
            localMd5Map = localMd5Json;
        }
    }
    // remove unneccessary resources.
    auto allKeys = localMd5Map->allKeys();
    for (const auto &key : allKeys) {
        if (!bundleMd5Json->hasKey(key)) {
            MWIOUtils::getInstance()->removeFile(this->_fullLocalAssetPath(key));
        }
    }
    MWIOUtils::getInstance()->copyFile(bundleMd5Path, localMd5Path);
    
    // save download file list
    _downloadFileList = queue<string>();
    allKeys = bundleMd5Json->allKeys();
    for (const auto &key : allKeys) {
        if (!localMd5Map->hasKey(key) || strcmp(localMd5Map->getString(key), bundleMd5Json->getString(key)) != 0) {
            _downloadFileList.push(key);
        }
    }
}

void MWAssetManager::_downloadNextAssetFile()
{
    // todo. continue with the progress of last accident which cause the failure of the update.
    if (!_downloadFileList.empty()) {
        string rpath = _downloadFileList.front();
        string downloadPath = this->_fullServerAssetPath(string(AM_ASSET_DIR) + "/" + rpath);
        string savePath = this->_fullLocalAssetPath(string(AM_ASSET_DIR) + "/" + rpath);
        
        _downloader->beginDownloading(downloadPath, savePath, __String::create(rpath), true);
    } else {
        this->_saveVersion();
    }
}

void MWAssetManager::_saveVersion()
{
    if (!MWIOUtils::getInstance()->copyFile(this->_fullLocalAssetPath(AM_VERSION_FILE), this->_fullLocalAssetPath(AM_LOCAL_VERSION_FILE))) {
        this->_delegateUpdateError(EAssetUpdateErrorType::IO_ERROR, "Failed to save local version.");
        return;
    }
    if (!MWIOUtils::getInstance()->copyFile(this->_fullLocalAssetPath(AM_BUNDLE_MD5_FILE), this->_fullLocalAssetPath(AM_LOCAL_MD5_FILE))) {
        this->_delegateUpdateError(EAssetUpdateErrorType::IO_ERROR, "Failed to save local md5 file.");
        return;
    }
    
    if (_localVersion != _newVersion) {
        _localVersion = _newVersion;
        this->_delegateVersionUpdated();
    }
}

string MWAssetManager::_fullLocalAssetPath(const std::string &path)
{
    return MWIOUtils::getInstance()->splicePath(_assetRoot, path);
}

string MWAssetManager::_fullServerAssetPath(const std::string &path)
{
    return MWIOUtils::getInstance()->splicePath(_serverUrl, path);
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
        // the asset path must occupy the highest priority.
        searchPaths.insert(searchPaths.cbegin(), assetPath);
        FileUtils::getInstance()->setSearchPaths(searchPaths);
        // set search order, the asset resource path should be the prepreerence.
        FileUtils::getInstance()->addSearchResolutionsOrder(assetPath, true);
        
        // add lua script package path.
#if MW_ENABLE_SCRIPT_BINDING
        vector<string> packages;
        packages.push_back(MWIOUtils::getInstance()->splicePath(this->_fullLocalAssetPath(AM_ASSET_DIR), AM_SCRIPT_DIR));
        MWLuaUtils::getInstance()->addPackagePaths(packages);
//        CCLOG("%s", MWLuaUtils::getInstance()->getPackagePath().c_str());
#endif
    }
}

void MWAssetManager::_delegateVersionCheckCompleted(bool latest, int fileCount, bool needUpdateProgram, const std::string &programUpdateUrl)
{
    if (_delegate) {
        _delegate->onVersionCheckCompleted(latest, fileCount, needUpdateProgram, programUpdateUrl);
    }
}

void MWAssetManager::_delegateVersionUpdated()
{
    if (_delegate) {
        _delegate->onVersionUpdated();
    }
}

void MWAssetManager::_delegateAssetFileDownloaded(const std::string &relativePath)
{
    if (_delegate) {
        _delegate->onAssetFileDownloaded(relativePath);
    }
}

void MWAssetManager::_delegateAssetFileDownloading(const std::string &relativePath, double downloaded, double totalToDownload)
{
    if (_delegate) {
        _delegate->onAssetFileDownloading(relativePath, downloaded, totalToDownload);
    }
}

void MWAssetManager::_delegateUpdateError(mwframework::EAssetUpdateErrorType errorType, const std::string &errorMsg)
{
    if (_delegate) {
        _delegate->onUpdateError(errorType, errorMsg);
    }
}

void MWAssetManager::onDownloadStarted(mwframework::MWHttpDownloader *downloader, cocos2d::Ref *userdata)
{
    MW_UNUSED_PARAM(downloader);
    
    string fileId = static_cast<__String *>(userdata)->getCString();
    if (fileId == string(AM_VERSION_FILE_ID)) {
        CCLOG("开始下载版本文件...");
    } else if (fileId == string(AM_CONFIG_FILE_ID)) {
        CCLOG("开始下载Asset配置文件...");
    } else if (fileId == string(AM_BUNDLE_MD5_FILE_ID)) {
        CCLOG("开始下载Bundle Md5文件...");
    } else {
        CCLOG("开始下载%s", static_cast<__String *>(userdata)->getCString());
    }
}

void MWAssetManager::onDownloading(mwframework::MWHttpDownloader *downloader, float progress, cocos2d::Ref *userdata)
{
    MW_UNUSED_PARAM(downloader);

    string fileId = static_cast<__String *>(userdata)->getCString();
    if (fileId != string(AM_VERSION_FILE_ID) && fileId != string(AM_CONFIG_FILE_ID) && fileId != string(AM_BUNDLE_MD5_FILE_ID)) {
        long totalSize = _fileSizeMap[fileId];
        this->_delegateAssetFileDownloading(fileId, (double) progress * totalSize, (double) totalSize);
    }
}

void MWAssetManager::onDownloadCompleted(mwframework::MWHttpDownloader *downloader, cocos2d::Ref *userdata)
{
    MW_UNUSED_PARAM(downloader);
    
    string fileId = static_cast<__String *>(userdata)->getCString();
    if (fileId == string(AM_VERSION_FILE_ID)) {
        this->_processAfterDownloadVersionFile();
    } else if (fileId == string(AM_CONFIG_FILE_ID)) {
        this->_processAfterDownloadAssetConfigFile();
    } else if (fileId == string(AM_BUNDLE_MD5_FILE_ID)) {
        if (_localVersion == _newVersion) {
            this->_saveVersion();
            this->_delegateVersionCheckCompleted(true, 0, false, "");
        } else {
            this->_processAfterDownloadBundleMd5File();
        }
    } else {
        this->_delegateAssetFileDownloaded(fileId);
        _downloadFileList.pop();
        this->_downloadNextAssetFile();
    }
}

void MWAssetManager::onDownloadFailed(mwframework::MWHttpDownloader *downloader, const std::string &errorMsg, cocos2d::Ref *userdata)
{
    MW_UNUSED_PARAM(downloader);
    
    CCLOG("下载错误: %s", errorMsg.c_str());
    
    if (_downloader->retry(userdata)) {
        CCLOG("重试下载...");
        return;
    }
    
    this->_delegateUpdateError(EAssetUpdateErrorType::NETWORK_ERROR, errorMsg);
}

MW_FRAMEWORK_END