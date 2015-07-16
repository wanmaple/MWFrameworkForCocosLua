#include "AppDelegate.h"
#include "CCLuaEngine.h"
#include "SimpleAudioEngine.h"
#include "cocos2d.h"
#include "lua_module_register.h"

#include "mwframework.h"

#define BUNDLE_RESOURCE_VERSION 1.00
#define CPP_PROGRAM_VERSION 0.00
#define DEVELOP_MODE false
#define SERVER_ASSET_ROOT_URL "http://120.25.123.138/mobile"

using namespace cocos2d;
using namespace std;
using namespace CocosDenshion;
using namespace mwframework;

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
    MWAssetManager::getInstance()->setBundleResourceVersion(BUNDLE_RESOURCE_VERSION);
    MWAssetManager::getInstance()->setProgramVersion(CPP_PROGRAM_VERSION);
    MWAssetManager::getInstance()->setDevelopMode(DEVELOP_MODE);
    MWAssetManager::getInstance()->setAssetRootUrl(SERVER_ASSET_ROOT_URL);
#endif
    
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
