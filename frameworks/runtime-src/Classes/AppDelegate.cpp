#include "AppDelegate.h"
#include "CCLuaEngine.h"
#include "SimpleAudioEngine.h"
#include "cocos2d.h"
#include "lua_module_register.h"

#include "mwframework.h"

#include "UpdateScene.h"

#define BUNDLE_VERSION "1.0.0-D2.987612"
#define CPP_PROGRAM_VERSION 1
#define DEVELOP_MODE true
#define SERVER_ASSET_ROOT_URL "http://localhost:8080/mobile"

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
    auto engine = LuaEngine::getInstance();
    ScriptEngineManager::getInstance()->setScriptEngine(engine);
    lua_State* L = engine->getLuaStack()->getLuaState();
    lua_module_register(L);
    register_all_mwframework(L);
	register_all_mwframework_manual(L);
	// can't register lua protobuf before mwframework, why?
	luaopen_protobuf_c(L);
    
    MWAssetManager::getInstance()->setBundleVersion(BUNDLE_VERSION);
    MWAssetManager::getInstance()->setProgramVersion(CPP_PROGRAM_VERSION);
    MWAssetManager::getInstance()->setDevelopMode(DEVELOP_MODE);
    MWAssetManager::getInstance()->setServerUrl(SERVER_ASSET_ROOT_URL);
    MWAssetManager::getInstance()->setAssetRootPath(MWIOUtils::getInstance()->splicePath(FileUtils::getInstance()->getWritablePath(), "Update"));
    
    if (MWAssetManager::getInstance()->isDevelopMode()) {
#ifdef MW_ENABLE_SCRIPT_BINDING
        MWLuaUtils::getInstance()->executeScriptFile("src/main.lua");
#endif
    } else {
        Director::getInstance()->runWithScene(UpdateScene::create());
    }

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
