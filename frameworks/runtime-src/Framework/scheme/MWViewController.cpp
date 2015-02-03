#include "MWViewController.h"
#include "MWGameScene.h"
#include "MWGameView.h"
#include "../lua/MWLuaUtils.h"
#include <new>

using namespace cocos2d;
using namespace std;

MW_FRAMEWORK_BEGIN

MWViewController *MWViewController::create(const std::string &identifier)
{
    auto pVc = new (nothrow) MWViewController();
    if (pVc && pVc->initWithIdentifier(identifier)) {
        pVc->autorelease();
        return pVc;
    }
    CC_SAFE_RELEASE(pVc);
    return nullptr;
}

bool MWViewController::initWithIdentifier(const std::string &identifier)
{
    if (identifier.size() <= 0) {
        return false;
    }
    _identifer = identifier;
    return true;
}

MWViewController::MWViewController()
: _scene(nullptr)
, _view(nullptr)
, _identifer()
, _scriptType(kScriptTypeNone)
{
#if CC_ENABLE_SCRIPT_BINDING
    ScriptEngineProtocol *pEngine = ScriptEngineManager::getInstance()->getScriptEngine();
    if (pEngine) {
        _scriptType = pEngine->getScriptType();
    }
#endif
}

MWViewController::~MWViewController()
{
    CC_SAFE_RELEASE(_view);
}

void MWViewController::viewDidLoad()
{
    if (!_view) {
        _view = MWGameView::create();
        _view->retain();
        _view->_controller = this;
    }
    
#if CC_ENABLE_SCRIPT_BINDING
    if (_scriptType == kScriptTypeLua) {
        MWLuaUtils::getInstance()->executePeertableFunction(this, "viewDidLoad", nullptr, nullptr, false);
    } else if (_scriptType == kScriptTypeJavascript) {
        // js todo
    }
#endif
}

void MWViewController::viewDidUnload()
{
#if CC_ENABLE_SCRIPT_BINDING
    if (_scriptType == kScriptTypeLua) {
        MWLuaUtils::getInstance()->executePeertableFunction(this, "viewDidUnload", nullptr, nullptr, false);
    } else if (_scriptType == kScriptTypeJavascript) {
        // js todo
    }
#endif
    
    if (_view && _view->getParent() && _view->_controller) {
        _view->removeFromParent();
        _view->_controller = nullptr;
    }
}

void MWViewController::didReceiveMemoryWarning()
{
    
}

MW_FRAMEWORK_END
