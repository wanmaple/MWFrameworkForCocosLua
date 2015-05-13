#include "MWViewSegue.h"
#include <new>

#include "cocos2d.h"
#include "MWGameView.h"
#include "MWGameScene.h"
#include "MWViewController.h"
#if MW_ENABLE_SCRIPT_BINDING
#include "../lua/MWLuaUtils.h"
#endif

using namespace cocos2d;
using namespace std;

MW_FRAMEWORK_BEGIN

MWViewSegue *MWViewSegue::create()
{
    auto pRet = new (nothrow) MWViewSegue();
    if (pRet && pRet->init()) {
        pRet->autorelease();
        return pRet;
    }
    CC_SAFE_RELEASE(pRet);
    return nullptr;
}

bool MWViewSegue::init()
{
    return true;
}

void MWViewSegue::viewReadyToSegue(MWViewController *controller)
{
    if (!controller) {
        CCLOG("Invalid view parameter.");
        return;
    }
    
#if MW_ENABLE_SCRIPT_BINDING
    if (_scriptType == kScriptTypeLua) {
        auto pParams = MWArrayList::create();
        pParams->appendObject(controller);
        auto pParamTypes = MWArrayList::create();
        pParamTypes->appendObject(__String::create("mw.ViewController"));
        MWLuaUtils::getInstance()->executePeertableFunction(this, "viewReadyToSegue", pParams, pParamTypes, false);
    } else if (_scriptType == kScriptTypeJavascript) {
        // js todo
    }
#endif
}

void MWViewSegue::viewDidSegue(MWViewController *controller)
{
    if (!controller) {
        CCLOG("Invalid scene parameter.");
        return;
    }
    
#if MW_ENABLE_SCRIPT_BINDING
    if (_scriptType == kScriptTypeLua) {
        auto pParams = MWArrayList::create();
        pParams->appendObject(controller);
        auto pParamTypes = MWArrayList::create();
        pParamTypes->appendObject(__String::create("mw.ViewController"));
        MWLuaUtils::getInstance()->executePeertableFunction(this, "viewDidSegue", pParams, pParamTypes, false);
    } else if (_scriptType == kScriptTypeJavascript) {
        // js todo
    }
#endif
}

void MWViewSegue::viewDidSegueBack(MWViewController *controller)
{
    if (!controller) {
        CCLOG("Invalid scene parameter.");
        return;
    }
    
#if MW_ENABLE_SCRIPT_BINDING
    if (_scriptType == kScriptTypeLua) {
        auto pParams = MWArrayList::create();
        pParams->appendObject(controller);
        auto pParamTypes = MWArrayList::create();
        pParamTypes->appendObject(__String::create("mw.ViewController"));
        MWLuaUtils::getInstance()->executePeertableFunction(this, "viewDidSegueBack", pParams, pParamTypes, false);
    } else if (_scriptType == kScriptTypeJavascript) {
        // js todo
    }
#endif
}

MW_FRAMEWORK_END