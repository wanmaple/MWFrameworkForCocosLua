#include "MWObject.h"

using namespace cocos2d;

MW_FRAMEWORK_BEGIN

MWObject::MWObject()
: _scriptType(kScriptTypeNone)
{
#if CC_ENABLE_SCRIPT_BINDING
    ScriptEngineProtocol *pEngine = ScriptEngineManager::getInstance()->getScriptEngine();
    if (pEngine) {
        _scriptType = pEngine->getScriptType();
    }
#endif
}

MWObject::~MWObject()
{
    
}

MW_UINT MWObject::hash()
{
    return (int)this;
}

MW_FRAMEWORK_END