#include "UpdateScene.h"

#include "cocos2d.h"
#include <new>

using namespace std;
using namespace cocos2d;
using namespace mwframework;

UpdateScene *UpdateScene::create()
{
    auto ret = new (nothrow) UpdateScene();
    if (ret && ret->init()) {
        MWAssetManager::getInstance()->setAssetUpdateDelegate(ret);
        ret->autorelease();
        return ret;
    }
    CC_SAFE_RELEASE(ret);
    return nullptr;
}

void UpdateScene::onVersionCheckCompleted(bool latest, int fileCount, bool needUpdateProgram, const std::string &programUpdateUrl)
{
    if (latest) {
        CCLOG("已经是最新版本...");
        MWLuaUtils::getInstance()->executeScriptFile("src/main.lua");
    } else {
        if (needUpdateProgram) {
            CCLOG("需要更新cpp程序，更新地址: %s", programUpdateUrl.c_str());
        } else {
            CCLOG("需要更新Asset，文件个数: %d", fileCount);
            MWAssetManager::getInstance()->beginUpdate();
        }
    }
}

void UpdateScene::onAssetFileToDownload(const std::string &relativePath, double totalToDownload)
{
    CCLOG("开始下载: %s 大小为: %d", relativePath.c_str(), (int) totalToDownload);
}

void UpdateScene::onAssetFileDownloading(const std::string &relativePath, double downloaded, double totalToDownload)
{
    
}

void UpdateScene::onAssetFileDownloaded(const std::string &relativePath)
{
    CCLOG("下载完毕: %s", relativePath.c_str());
}

void UpdateScene::onVersionUpdated()
{
    CCLOG("版本更新完毕.");
    MWLuaUtils::getInstance()->executeScriptFile("src/main.lua");
}

void UpdateScene::onUpdateError(mwframework::EAssetUpdateErrorType errorType, const std::string &errorMsg)
{
    CCLOG("更新出错: %s", errorMsg.c_str());
}

void UpdateScene::onEnter()
{
    CCLOG("%s", FileUtils::getInstance()->getWritablePath().c_str());
    
    MWAssetManager::getInstance()->checkVersion();
    
    Scene::onEnter();
}

void UpdateScene::onExit()
{
    Scene::onExit();
}