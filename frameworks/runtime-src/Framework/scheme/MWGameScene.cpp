#include "MWGameScene.h"
#include "cocos2d.h"
#include "MWViewController.h"
#include "MWGameView.h"
#include "../lua/MWLuaUtils.h"
#include <new>

using namespace cocos2d;
using namespace std;

MW_FRAMEWORK_BEGIN

MWGameScene *MWGameScene::create()
{
    auto pScene = new (nothrow) MWGameScene();
    if (pScene && pScene->init()) {
        pScene->autorelease();
        return pScene;
    }
    CC_SAFE_RELEASE(pScene);
    return nullptr;
}

MWGameScene *MWGameScene::createWithParams(mwframework::MWDictionary *params)
{
    auto pScene = new (nothrow) MWGameScene();
    if (pScene && pScene->init(params)) {
        pScene->autorelease();
        return pScene;
    }
    CC_SAFE_RELEASE(pScene);
    return nullptr;
}

bool MWGameScene::init(MWDictionary *params)
{
    _viewControllers = new (nothrow) MWArrayList();
    _rootViewController = MWViewController::create();
    if (_params && _viewControllers && _rootViewController) {
        this->loadViewController(_rootViewController);
        if (params) {
            _params = params->clone();
            // the copy is autoreleased.
            _params->retain();
        } else {
            _params = new (nothrow) MWDictionary();
        }
        return true;
    }
    CC_SAFE_RELEASE(_params);
    CC_SAFE_RELEASE(_viewControllers);
    return false;
}

MWGameScene::MWGameScene()
: _params(nullptr)
, _viewControllers(nullptr)
, _rootViewController(nullptr)
{
    
}

MWGameScene::~MWGameScene()
{
    CC_SAFE_RELEASE(_params);
    CC_SAFE_RELEASE(_viewControllers);
    CC_SAFE_RELEASE(_rootViewController);
}

void MWGameScene::onEnter()
{
    Scene::onEnter();
    
#if CC_ENABLE_SCRIPT_BINDING
    if (_scriptType == kScriptTypeLua) {
        MWLuaUtils::getInstance()->executePeertableFunction(this, "onEnter", nullptr, nullptr, false);
    } else if (_scriptType == kScriptTypeJavascript) {
        // js todo
    }
#endif
}

void MWGameScene::onExit()
{
#if CC_ENABLE_SCRIPT_BINDING
    if (_scriptType == kScriptTypeLua) {
        MWLuaUtils::getInstance()->executePeertableFunction(this, "onExit", nullptr, nullptr, false);
    } else if (_scriptType == kScriptTypeJavascript) {
        // js todo
    }
#endif
    
    // unload all view controllers.
    this->unloadAllViewControllers();
    
    Scene::onExit();
}

void MWGameScene::onEnterTransitionDidFinish()
{
    Scene::onEnterTransitionDidFinish();
    
#if CC_ENABLE_SCRIPT_BINDING
    if (_scriptType == kScriptTypeLua) {
        MWLuaUtils::getInstance()->executePeertableFunction(this, "onEnterTransitionDidFinish", nullptr, nullptr, false);
    } else if (_scriptType == kScriptTypeJavascript) {
        // js todo
    }
#endif
}

void MWGameScene::onExitTransitionDidStart()
{
#if CC_ENABLE_SCRIPT_BINDING
    if (_scriptType == kScriptTypeLua) {
        MWLuaUtils::getInstance()->executePeertableFunction(this, "onExitTransitionDidStart", nullptr, nullptr, false);
    } else if (_scriptType == kScriptTypeJavascript) {
        // js todo
    }
#endif
    
    Scene::onExitTransitionDidStart();
}

void MWGameScene::addParameter(const std::string &key, double param)
{
    _params->setObjectForKey(key, param);
}

void MWGameScene::addParameter(const std::string &key, bool param)
{
    _params->setObjectForKey(key, param);
}

void MWGameScene::addParameter(const std::string &key, const std::string &param)
{
    _params->setObjectForKey(key, param);
}

void MWGameScene::addParameter(const std::string &key, cocos2d::Ref *param)
{
    _params->setObjectForKey(key, param);
}

double MWGameScene::getNumberParameter(const std::string &key) MW_NOEXCEPTION(MW_WHETHER_THROW_EXCEPTION)
{
    return _params->numberForKey(key);
}

bool MWGameScene::getBooleanParameter(const std::string &key) MW_NOEXCEPTION(MW_WHETHER_THROW_EXCEPTION)
{
    return _params->booleanForKey(key);
}

std::string MWGameScene::getStringParameter(const std::string &key) MW_NOEXCEPTION(MW_WHETHER_THROW_EXCEPTION)
{
    return _params->stringForKey(key);
}

cocos2d::Ref *MWGameScene::getRefParameter(const std::string &key) MW_NOEXCEPTION(MW_WHETHER_THROW_EXCEPTION)
{
    return _params->objectForKey(key);
}

void MWGameScene::loadViewController(mwframework::MWViewController *controller) MW_NOEXCEPTION(MW_WHETHER_THROW_EXCEPTION)
{
    // check parameter.
    if (!controller) {
        MW_THROW_EXCEPTION(1006);
    }
    controller->_scene = this;
    controller->viewDidLoad();
    this->addChild(controller->view());
    _viewControllers->appendObject(controller);
}

void MWGameScene::unloadViewController(mwframework::MWViewController *controller) MW_NOEXCEPTION(MW_WHETHER_THROW_EXCEPTION)
{
    // check parameter.
    if (!controller) {
        MW_THROW_EXCEPTION(1006);
    }
    if (_viewControllers->indexOfObject(controller) > 0) {
        controller->view()->removeFromParent();
        controller->_scene = nullptr;
        controller->viewDidUnload();
        _viewControllers->removeObject(controller);
    }
}

void MWGameScene::unloadViewControllerByIdentifier(const std::string &identifier)
{
    MWViewController *pVc = this->getViewControllerByIdentifier(identifier);
    if (pVc) {
        this->unloadViewController(pVc);
    }
}

MWViewController *MWGameScene::getViewControllerByIdentifier(const std::string &identifier)
{
    if (identifier.size() <= 0) {
        return nullptr;
    }
    MWViewController *pVc = nullptr;
    for (MW_UINT i = 0; i < _viewControllers->count(); ++i) {
        pVc = static_cast<MWViewController*>(_viewControllers->objectAtIndex(i));
        if (pVc->getIdentifier() == identifier) {
            return pVc;
        }
    }
    return nullptr;
}

void MWGameScene::unloadAllViewControllers()
{
    MWViewController *pVc = nullptr;
    while (_viewControllers->count() > 0) {
        pVc = static_cast<MWViewController*>(_viewControllers->objectAtIndex(0));
        this->unloadViewController(pVc);
    }
    _viewControllers->clear();
}

MW_FRAMEWORK_END