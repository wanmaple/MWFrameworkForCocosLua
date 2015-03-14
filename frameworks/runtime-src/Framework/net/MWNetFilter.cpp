#include "MWNetFilter.h"

#include "cocos2d.h"
#include "../lua/MWLuaUtils.h"

#include <new>

using namespace cocos2d;
using namespace std;

MW_FRAMEWORK_BEGIN

MWNetFilter *MWNetFilter::create()
{
    auto pRet = new (nothrow) MWNetFilter();
    if (pRet) {
        pRet->autorelease();
        return pRet;
    }
    return nullptr;
}

void MWNetFilter::filterSuccessfulMessage(mwframework::MWNetResponse *response)
{
#if MW_ENABLE_SCRIPT_BINDING
    if (_scriptType == kScriptTypeLua) {
        MWArrayList *pParams = MWArrayList::create();
        pParams->appendObject(response);
        MWArrayList *pParamTypes = MWArrayList::create();
        pParamTypes->appendObject("mw.NetResponse");
        MWLuaUtils::getInstance()->executePeertableFunction(this, "filterSuccessfulMessage", pParams, pParamTypes, false);
    } else if (_scriptType == kScriptTypeJavascript) {
        // todo js
    }
#endif
}

void MWNetFilter::filterFailedMessage(mwframework::MWNetResponse *response)
{
#if MW_ENABLE_SCRIPT_BINDING
    if (_scriptType == kScriptTypeLua) {
        MWArrayList *pParams = MWArrayList::create();
        pParams->appendObject(response);
        MWArrayList *pParamTypes = MWArrayList::create();
        pParamTypes->appendObject("mw.NetResponse");
        MWLuaUtils::getInstance()->executePeertableFunction(this, "filterFailedMessage", pParams, pParamTypes, false);
    } else if (_scriptType == kScriptTypeJavascript) {
        // todo js
    }
#endif
}

MW_FRAMEWORK_END
