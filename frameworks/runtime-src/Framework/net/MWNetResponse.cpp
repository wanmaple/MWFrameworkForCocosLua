#include "MWNetResponse.h"
#include "MWNetRequest.h"

#include <new>

using namespace std;

MW_FRAMEWORK_BEGIN

MWNetResponse *MWNetResponse::create(const std::string &protocolId, const std::string &body, MWNetRequest *request)
{
    auto pResponse = new (nothrow) MWNetResponse();
    if (pResponse && pResponse->init(protocolId, body, request)) {
        pResponse->autorelease();
        return pResponse;
    }
    CC_SAFE_RELEASE(pResponse);
    return nullptr;
}

bool MWNetResponse::init(const std::string &protocolId, const std::string &body, MWNetRequest *request)
{
    if (protocolId.size() <= 0 || body.size() <= 0 || !request) {
        return false;
    }
    
    _protocolId = protocolId;
    _body = body;
    _relatedRequest = request;
    _relatedRequest->retain();
    
    return true;
}

MWNetResponse::~MWNetResponse()
{
    CC_SAFE_RELEASE(_relatedRequest);
}

MW_FRAMEWORK_END