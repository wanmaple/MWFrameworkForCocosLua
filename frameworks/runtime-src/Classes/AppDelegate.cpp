#include "AppDelegate.h"
#include "CCLuaEngine.h"
#include "SimpleAudioEngine.h"
#include "cocos2d.h"
#include "lua_module_register.h"

#include "mwframework.h"

#include "TestScene.h"

using namespace CocosDenshion;

USING_NS_CC;
using namespace std;
using namespace mwframework;

class TestDownloadDelegate : public mwframework::IHttpDownloaderDelegate
{
    /**
     * Delegate when the download task starts.
     *
     * @param downloader Related downloader of the task.
     */
    virtual void onDownloadStarted(MWHttpDownloader *downloader, cocos2d::Ref *userdata)
    {
        auto pStr = static_cast<__String *>(userdata);
        CCLOG("Download start: %s", pStr->getCString());
    }
    /**
     * Delegate when the download task executes.
     *
     * @param downloader Related downloader of the task.
     * @param progress Downloading progress.
     */
    virtual void onDownloading(MWHttpDownloader *downloader, float progress, cocos2d::Ref *userdata)
    {
        CCLOG("Progress: %f", progress);
    }
    /**
     * Delegate when the download task completes.
     *
     * @param downloader Related downloader of the task.
     */
    virtual void onDownloadCompleted(MWHttpDownloader *downloader, cocos2d::Ref *userdata)
    {
        auto pStr = static_cast<__String *>(userdata);
        CCLOG("Download complete: %s", pStr->getCString());
    }
    /**
     * Delegate when the download task fails.
     *
     * @param downloader Related downloader of the task.
     * @param errorMsg Encountered error message.
     */
    virtual void onDownloadFailed(MWHttpDownloader *downloader, const std::string &errorMsg, cocos2d::Ref *userdata)
    {
        CCLOG("Download failed. Message: %s", errorMsg.c_str());
    }
};

AppDelegate::AppDelegate()
{
}

AppDelegate::~AppDelegate()
{
    SimpleAudioEngine::end();
}

//if you want a different context,just modify the value of glContextAttrs
//it will takes effect on all platforms
void AppDelegate::initGLContextAttrs()
{
    //set OpenGL context attributions,now can only set six attributions:
    //red,green,blue,alpha,depth,stencil
    GLContextAttrs glContextAttrs = {8, 8, 8, 8, 24, 8};

    GLView::setGLContextAttrs(glContextAttrs);
}

bool AppDelegate::applicationDidFinishLaunching()
{
    auto engine = LuaEngine::getInstance();
    ScriptEngineManager::getInstance()->setScriptEngine(engine);
    lua_State* L = engine->getLuaStack()->getLuaState();
    lua_module_register(L);
    
//    std::string savePath = cocos2d::FileUtils::getInstance()->getWritablePath() + string("Resource/icon.jpg");
//    CCLOG("%s", savePath.c_str());
//    auto downloader = new mwframework::MWHttpDownloader();
//    downloader->setDelegate(new TestDownloadDelegate());
//    downloader->beginDownloading("http://120.25.123.138/mobile/Resource/icon.jpg", savePath, __String::create(savePath), false);
    
#if MW_ENABLE_SCRIPT_BINDING
#ifdef DEBUG
    lua_pushboolean(L, true);
    lua_setglobal(L, "DEBUG");
#endif
    
    register_all_mwframework(L);
    register_all_mwframework_manual(L);

    if (engine->executeScriptFile("src/main.lua")) {
        return false;
    }
#endif

    return true;
}

// This function will be called when the app is inactive. When comes a phone call,it's be invoked too
void AppDelegate::applicationDidEnterBackground()
{
    Director::getInstance()->stopAnimation();

    SimpleAudioEngine::getInstance()->pauseBackgroundMusic();
}

// this function will be called when the app is active again
void AppDelegate::applicationWillEnterForeground()
{
    Director::getInstance()->startAnimation();

    SimpleAudioEngine::getInstance()->resumeBackgroundMusic();
}
