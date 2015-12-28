#include "MWNetRequest.h"

#include <new>

using namespace std;

MW_FRAMEWORK_BEGIN

MWNetRequest *MWNetRequest::create(const std::string &protocolId, MWBinaryData *body)
{
    auto pRequest = new (nothrow) MWNetRequest();
    if (pRequest && pRequest->init(protocolId, body)) {
        pRequest->autorelease();
        return pRequest;
    }
    CC_SAFE_RELEASE(pRequest);
    return nullptr;
}

bool MWNetRequest::init(const std::string &protocolId, MWBinaryData *body)
{
    if (protocolId.size() <= 0) {
        return false;
    }
    
    _protocolId = protocolId;
    _body = body;
    
    return true;
}

MWNetRequest::~MWNetRequest()
{
    
}

MW_FRAMEWORK_END