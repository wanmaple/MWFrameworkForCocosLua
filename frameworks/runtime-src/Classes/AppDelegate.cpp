#include "AppDelegate.h"
#include "CCLuaEngine.h"
#include "SimpleAudioEngine.h"
#include "cocos2d.h"
#include "lua_module_register.h"

#include "mwframework.h"

#define BUNDLE_RESOURCE_VERSION 1.02
#define CPP_PROGRAM_VERSION 0.00
#define DEVELOP_MODE false
#define SERVER_ASSET_ROOT_URL "http://120.25.123.138/mobile/asset"

using namespace cocos2d;
using namespace std;
using namespace CocosDenshion;
using namespace mwframework;

class UpdateScene : public MWGameScene, public IAssetUpdateDelegate
{
public:
    static UpdateScene *create()
    {
        auto ret = new (nothrow) UpdateScene();
        if (ret && ret->init()) {
            ret->autorelease();
            return ret;
        }
        CC_SAFE_RELEASE(ret);
        return nullptr;
    }
    
    /**
     * Delegate when the version checking is over.
     */
    void onVersionCheckCompleted(bool latest, int fileCount, bool needUpdateProgram, const std::string &programUpdateUrl)
    {
        if (latest) {
            CCLOG("已经是最新版本...");
        } else {
            if (needUpdateProgram) {
                CCLOG("需要更新cpp程序，更新地址: %s", programUpdateUrl.c_str());
            } else {
                CCLOG("需要更新Asset，文件个数: %d", fileCount);
            }
        }
    }
    /**
     * Delegate when the single file is downloading.
     */
    void onAssetFileDownloading(const std::string &filePath, float progress, long totalToDownload)
    {
        
    }
    /**
     * Delegate when the single file is updated.
     */
    void onAssetFileDownloaded(const std::string &filePath)
    {
        CCLOG("%s下载完成", filePath.c_str());
    }
    /**
     * Delegate when the version is updated.
     */
    void onVersionUpdated()
    {
        CCLOG("版本更新完毕.");
        
        auto engine = LuaEngine::getInstance();
        ScriptEngineManager::getInstance()->setScriptEngine(engine);
        lua_State* L = engine->getLuaStack()->getLuaState();
        lua_module_register(L);
        
#ifdef MW_ENABLE_SCRIPT_BINDING
#ifdef DEBUG
        lua_pushboolean(L, true);
        lua_setglobal(L, "DEBUG");
#endif
        
        register_all_mwframework(L);
        register_all_mwframework_manual(L);
        
        if (engine->executeScriptFile("src/main.lua")) {
            CCLOG("执行main脚本出错...");
        }
#endif
    }
    /**
     * Delegate when download failed.
     */
    void onUpdateError(EAssetUpdateErrorType errorType, const std::string &errorMsg)
    {
        CCLOG("更新出错: %s", errorMsg.c_str());
    }
    
    void onEnter() override
    {
        CCLOG("%s", FileUtils::getInstance()->getWritablePath().c_str());
        
        MWAssetManager::getInstance()->setBundleResourceVersion(BUNDLE_RESOURCE_VERSION);
        MWAssetManager::getInstance()->setProgramVersion(CPP_PROGRAM_VERSION);
        MWAssetManager::getInstance()->setDevelopMode(DEVELOP_MODE);
        MWAssetManager::getInstance()->setAssetRootUrl(SERVER_ASSET_ROOT_URL);
        
        MWAssetManager::getInstance()->setAssetUpdateDelegate(this);
        MWAssetManager::getInstance()->checkVersion();
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
    FileUtils::getInstance()->addSearchPath("res");
    FileUtils::getInstance()->addSearchPath("src");
    
#ifdef MW_ENABLE_ASSET_UPDATE
    Director::getInstance()->runWithScene(UpdateScene::create());
#else
    auto engine = LuaEngine::getInstance();
    ScriptEngineManager::getInstance()->setScriptEngine(engine);
    lua_State* L = engine->getLuaStack()->getLuaState();
    lua_module_register(L);
    
#ifdef MW_ENABLE_SCRIPT_BINDING
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
