#include "MWAssetManager.h"
#include "../json/MWJsonStructure.h"
#include "../platform/MWIOUtils.h"
#include "../net/http/MWHttpDownloader.h"
#include "cocos2d.h"

#define AM_VERSION_FILE "version.bin"
//#define AM_GLOBAL_MD5_FILE "global.md5.bin"
#define AM_BUNDLE_MD5_DIRECTORY "BundleMd5"
#define AM_BUNDLE_MD5_FILE "bundle.md5.bin"
#define AM_ASSET_CONFIG_FILE "asset.config.bin"
#define AM_MAIN_MODULE_NAME "am.main"

// version description file keys
#define AM_VERSION_KEY "version"
#define AM_MIN_PROGRAM_VERSION_KEY "min_program_version"
#define AM_PROGRAM_UPDATE_URL_KEY "program_update_url"

using namespace std;
using namespace cocos2d;

MW_FRAMEWORK_BEGIN

MWAssetManager::MWAssetManager()
: _programVersion(0.0f)
, _bundleAssetVersion(0.0f)
, _assetRootUrl()
, _localVersion(0.0f)
, _isDevelopMode(false)
, _serverVersion(0.0f)
, _downloadCache()
, _updatingModuleList()
, _moduleUpdating(false)
, _minProgramVersion(0.0f)
, _programUpdateUrl()
, _jsonConfig(nullptr)
, _jsonBundleMd5(nullptr)
, _globalMd5NeedFlush(false)
, _assetUpdateDelegate(nullptr)
, _downloader(nullptr)
, _downloadFileType()
, _localAssetPath()
, _serverAssetDir()
, _localAssetDir()
{
    _downloader = new MWHttpDownloader();
    _downloader->setDelegate(this);
    
    _localVersion = UserDefault::getInstance()->getFloatForKey(AM_VERSION_KEY);
}

MWAssetManager::~MWAssetManager()
{
    _downloader->destroy();
    CC_SAFE_RELEASE(_jsonBundleMd5);
    CC_SAFE_RELEASE(_jsonConfig);
}

void MWAssetManager::setAssetRootUrl(const std::string &assetRootUrl)
{
    _assetRootUrl = assetRootUrl;
    if (_assetRootUrl.at(_assetRootUrl.size() - 1) != '/') {
        _assetRootUrl.append("/");
    }
}

string MWAssetManager::fullLocalAssetPath(const std::string &filePath)
{
    static string localAssetPath = MWIOUtils::getInstance()->splicePath(FileUtils::getInstance()->getWritablePath(), _localAssetDir);
    return MWIOUtils::getInstance()->splicePath(localAssetPath, filePath);
}

void MWAssetManager::configSearchPath()
{
    // clear current search path.
    this->clearSearchPath();
    
    // config new search path: WritablePath/Bundle
    vector<string> searchPaths;
    searchPaths.push_back(this->fullLocalAssetPath(""));
    if (_localAssetDir.length() > 0) {
        searchPaths.push_back(this->fullLocalAssetPath(_localAssetDir));
    }
    
    FileUtils::getInstance()->setSearchPaths(searchPaths);
}

void MWAssetManager::clearSearchPath()
{
    FileUtils::getInstance()->setSearchPaths(std::vector<std::string>());
    FileUtils::getInstance()->purgeCachedEntries();
}

void MWAssetManager::checkVersion()
{
    string localAssetPath = MWIOUtils::getInstance()->splicePath(FileUtils::getInstance()->getWritablePath(), _localAssetPath);
    if (localAssetPath.at(localAssetPath.length() - 1) != '/') {
        localAssetPath.append("/");
    }
    
    if (!MWIOUtils::getInstance()->fileExists(localAssetPath)) {
        MWIOUtils::getInstance()->createDirectory(localAssetPath);
    }
    
    // check bundle asset version, deal with sth. if local version is not the latest.
    if (_localVersion < _bundleAssetVersion) {
        this->clearSearchPath();
        
        // download related md5 file of bundle asset version.
        this->downloadBundleMd5File();
        // config search path.
        this->configSearchPath();
    } else {
        // download version description file.
        this->downloadVersionFile();
    }
}

void MWAssetManager::downloadBundleMd5File()
{
    // confirm download address
    string downloadPath = MWIOUtils::getInstance()->splicePath(_assetRootUrl, AM_BUNDLE_MD5_DIRECTORY);
    const char * versionStr = __String::createWithFormat("%.2f", _bundleAssetVersion)->getCString();
    downloadPath = MWIOUtils::getInstance()->splicePath(downloadPath, versionStr);
    downloadPath = MWIOUtils::getInstance()->splicePath(downloadPath, AM_BUNDLE_MD5_FILE);
    
    // local bundle md5 file path
    string savePath = this->fullLocalAssetPath(AM_BUNDLE_MD5_FILE);
    
    // download
    _downloadFileType = BUNDLE_MD5_FILE;
    _downloader->beginDownloading(downloadPath, savePath);
}

void MWAssetManager::mergeMd5File()
{
    // retrieve bundle md5.
    auto jsonBundleMd5 = MWJsonObject::createWithFile(this->fullLocalAssetPath(AM_BUNDLE_MD5_FILE));
    
    // retrieve global md5, create if non-exist.
    string globalMd5Path = this->fullLocalAssetPath(AM_GLOBAL_MD5_FILE);
    if (!MWIOUtils::getInstance()->fileExists(globalMd5Path)) {
        MWJsonObject *jsonEmpty = MWJsonObject::create();
        string json = jsonEmpty->toString();
        MWIOUtils::getInstance()->writeDataToFile(json.c_str(), json.size(), globalMd5Path);
    }
    auto jsonGlobalMd5 = MWJsonObject::createWithFile(globalMd5Path);
    
    // merge
    auto filenames = jsonBundleMd5->allKeys();
    for (auto filename : filenames) {
        jsonGlobalMd5->putString(filename, jsonBundleMd5->getString(filename));
        // delete old file.
        string oldPath = this->fullLocalAssetPath(filename);
        MWIOUtils::getInstance()->removeFile(oldPath);
    }
    
    // write new global md5.
    string json = jsonGlobalMd5->toString();
    MWIOUtils::getInstance()->writeDataToFile(json.c_str(), json.length(), globalMd5Path);
    
    // save version.
    this->saveVersion(_bundleAssetVersion);
}

void MWAssetManager::saveVersion(float version)
{
    _localVersion = version;
    UserDefault::getInstance()->setFloatForKey(AM_VERSION_KEY, version);
    UserDefault::getInstance()->flush();
}

void MWAssetManager::downloadVersionFile()
{
    string downloadPath = MWIOUtils::getInstance()->splicePath(_assetRootUrl, AM_VERSION_FILE);
    string savePath = this->fullLocalAssetPath(AM_VERSION_FILE);
    
    _downloadFileType = VERSION_FILE;
    _downloader->beginDownloading(downloadPath, savePath);
}

void MWAssetManager::downloadConfigFile()
{
    string downloadPath = MWIOUtils::getInstance()->splicePath(_assetRootUrl, AM_ASSET_CONFIG_FILE);
    string savePath = this->fullLocalAssetPath(AM_ASSET_CONFIG_FILE);
    
    _downloadFileType = CONFIG_FILE;
    _downloader->beginDownloading(downloadPath, savePath);
}

void MWAssetManager::downloadModuleFile()
{
    if (_updatingModuleList.size() <= 0) {
        return;
    }
    
    // retreive first module
    string moduleName = _updatingModuleList[0];
    
    // check download cache
    if (_downloadCache.find(moduleName) == _downloadCache.end() || _downloadCache[moduleName].size() <= 0) {
        return;
    }
    
    auto downloadFileList = _downloadCache[moduleName];
    string filePath = downloadFileList[0];
    
    if (this->isFileUpdated(filePath)) {
        CCLOG("Already updated by other module: %s", filePath.c_str());
        this->processAfterSingleModleFileDownload(moduleName);
        return;
    }
    
    _moduleUpdating = true;
    
    // download
    string downloadPath = MWIOUtils::getInstance()->splicePath(_assetRootUrl, _serverAssetDir);
    downloadPath = MWIOUtils::getInstance()->splicePath(downloadPath, filePath);
    
    string savePath = this->fullLocalAssetPath(filePath);
    
    _downloadFileType = MODULE_FILE;
    
    _downloader->beginDownloading(downloadPath, savePath, __String::create(moduleName), false);
}

void MWAssetManager::onDownloadStarted(mwframework::MWHttpDownloader *downloader, cocos2d::Ref *userdata)
{
    MW_UNUSED_PARAM(downloader);
    
    if (_downloadFileType == BUNDLE_MD5_FILE) {
        this->mergeMd5File();
        this->downloadVersionFile();
    } else if (_downloadFileType == VERSION_FILE) {
        this->processAfterVersionFileDownload();
    } else if (_downloadFileType == CONFIG_FILE) {
        this->processAfterConfigFileDownload();
    } else if (_downloadFileType == MODULE_FILE) {
        __String *pStr = static_cast<__String *>(userdata);
        this->processAfterSingleModleFileDownload(pStr->getCString());
    }
}

void MWAssetManager::onDownloading(mwframework::MWHttpDownloader *downloader, float progress, cocos2d::Ref *userdata)
{
    MW_UNUSED_PARAM(downloader);
    MW_UNUSED_PARAM(progress);
    MW_UNUSED_PARAM(userdata);
}

void MWAssetManager::onDownloadFailed(mwframework::MWHttpDownloader *downloader, const std::string &errorMsg, cocos2d::Ref *userdata)
{
    MW_UNUSED_PARAM(downloader);
    
    CCLOG("Download file error: %s", errorMsg.c_str());
    
    if (_downloader->retry(userdata)) {
        
    }
}

MW_FRAMEWORK_END