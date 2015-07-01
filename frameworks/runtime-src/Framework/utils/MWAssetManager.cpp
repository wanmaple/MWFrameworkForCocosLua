#include "MWAssetManager.h"
#include "../json/MWJsonStructure.h"
#include "../platform/MWIOUtils.h"
#include "../net/http/MWHttpDownloader.h"
#include "cocos2d.h"

using namespace std;
using namespace cocos2d;

MW_FRAMEWORK_BEGIN

MWAssetManager::MWAssetManager()
: _programVersion(0.0f)
, _assetVersion(0.0f)
, _assetRootUrl()
, _localVersion(0.0f)
, _isDevelopMode(false)
, _serverVersion(0.0f)
, _downloadCache()
, _updatingModuleList()
, _moduleUpdating(false)
, _copyFileList()
, _minProgramVersion(0.0f)
, _programUpdateUrl()
, _jsonConfig(nullptr)
, _jsonBundleMd5(nullptr)
, _globalMd5NeedFlush(false)
, _delegate(nullptr)
, _downloader(nullptr)
, _localAssetPath()
{
    
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

void MWAssetManager::configSearchPath()
{
    // clear current search path.
    this->clearSearchPath();
    
    // config new search path: WritablePath/Bundle
    vector<string> searchPaths;
    searchPaths.push_back(this->fullLocalAssetPath(""));
    
    FileUtils::getInstance()->setSearchPaths(searchPaths);
}

void MWAssetManager::clearSearchPath()
{
    FileUtils::getInstance()->setSearchPaths(std::vector<std::string>());
    FileUtils::getInstance()->purgeCachedEntries();
}

void MWAssetManager::setCopyFileList(const std::vector<std::string> &fileList)
{
    _copyFileList = fileList;
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
    
    if (_localVersion < _assetVersion) {
        this->clearSearchPath();
        this->downloadBundleMd5File();
        this->copyFiles(_copyFileList);
        this->configSearchPath();
    } else {
        this->downloadVersionFile();
    }
}

MW_FRAMEWORK_END