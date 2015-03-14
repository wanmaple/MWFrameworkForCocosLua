#include "MWNetProtocol.h"

#include "MWNetHandler.h"

#include <new>

using namespace std;

MW_FRAMEWORK_BEGIN

MWNetProtocol *MWNetProtocol::create(const std::string &protocolId, const std::string &serviceId, mwframework::MWNetHandler *handler)
{
    auto pRet = new (nothrow) MWNetProtocol();
    if (pRet && pRet->init(protocolId, serviceId, handler)) {
        pRet->autorelease();
        return pRet;
    }
    CC_SAFE_RELEASE(pRet);
    return nullptr;
}

bool MWNetProtocol::init(const std::string &protocolId, const std::string &serviceId, mwframework::MWNetHandler *handler)
{
    if (protocolId.size() <= 0 || serviceId.size() <= 0 || !handler) {
        return false;
    }
    
    _protocolId = protocolId;
    _serviceId = serviceId;
    _relatedHandler = handler;
    _relatedHandler->retain();
    
    return true;
}

MWNetProtocol::~MWNetProtocol()
{
    CC_SAFE_RELEASE(_relatedHandler);
}

MW_FRAMEWORK_END