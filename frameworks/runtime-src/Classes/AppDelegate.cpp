#include "AppDelegate.h"
#include "CCLuaEngine.h"
#include "SimpleAudioEngine.h"
#include "cocos2d.h"
#include "lua_module_register.h"

#include "mwframework.h"

using namespace CocosDenshion;

USING_NS_CC;
using namespace std;

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
    
    auto pScene = Scene::create();
    auto pLayer = LayerColor::create(Color4B(255, 0, 0, 200));
    auto pZip = mwframework::MWZipData::createWithExistingFile("res/493.zip");
    auto pGif = mwframework::MWGifSprite::createWithRawData(pZip->getCompressedFileData("493.gif"));
    pGif->setPosition(Director::getInstance()->getWinSize().width * 0.5, Director::getInstance()->getWinSize().height * 0.5);
    pGif->setSpeedRatio(1.0f);
    pGif->setScale(2.5f, 2.5f);
    pLayer->addChild(pGif);
    auto pGif2 = mwframework::MWGifSprite::createWithFile("res/GIF/483.gif");
    pGif2->setPosition(Director::getInstance()->getWinSize().width * 0.3, Director::getInstance()->getWinSize().height * 0.3);
    pGif2->setSpeedRatio(1.0f);
    pGif2->setScale(2.5f, 2.5f);
    pLayer->addChild(pGif2);
    auto pGif3 = mwframework::MWGifSprite::createWithFile("res/GIF/484.gif");
    pGif3->setPosition(Director::getInstance()->getWinSize().width * 0.7, Director::getInstance()->getWinSize().height * 0.3);
    pGif3->setSpeedRatio(1.0f);
    pGif3->setScale(2.5f, 2.5f);
    pLayer->addChild(pGif3);
    auto gifZip = mwframework::MWZipData::createWithExistingFile("res/GIF/pokemon_gif5.rc");
    auto data = gifZip->getCompressedFileData("487_o.gif", "7ujm,lp-");
    auto pGif4 = mwframework::MWGifSprite::createWithRawData(data);
    pGif4->setPosition(Director::getInstance()->getWinSize().width * 0.5, Director::getInstance()->getWinSize().height * 0.85);
    pGif4->setSpeedRatio(1.0f);
    pGif4->setScale(2.5f, 2.5f);
    pLayer->addChild(pGif4);
    pScene->addChild(pLayer);
    Director::getInstance()->runWithScene(pScene);
    
    mwframework::MWIOUtils::getInstance()->createDirectory("res/aa/bb/cc");
    CCLOG("%s", mwframework::MWIOUtils::getInstance()->resourcePath("res/aa/bb/cc/111.txt").c_str());
    mwframework::MWIOUtils::getInstance()->createFile("res/aa/bb/cc/111.txt");
    mwframework::MWIOUtils::getInstance()->writeDataToFile("abcdefg", 7, "res/aa/bb/cc/111.txt");
    
    Director::getInstance()->getScheduler()->schedule([this] (float dt) {
        printf("Used memory: %lf MB\n", mwframework::MWSystemHelper::getInstance()->getCurrentUsedMemory());
    }, this, 5.0f, CC_REPEAT_FOREVER, 0.0f, false, "MEMORY_SCHEDULER");
    
    
    return true;

    // If you want to use Quick-Cocos2d-X, please uncomment below code
    // register_all_quick_manual(L);

    if (engine->executeScriptFile("src/main.lua")) {
        return false;
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
