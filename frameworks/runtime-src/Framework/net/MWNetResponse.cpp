#include "MWNetResponse.h"
#include "MWNetRequest.h"

#include <new>

using namespace std;

MW_FRAMEWORK_BEGIN

MWNetResponse *MWNetResponse::create(const std::string &protocolId, MWBinaryData *body, MWNetRequest *request)
{
    auto pResponse = new (nothrow) MWNetResponse();
    if (pResponse && pResponse->init(protocolId, body, request)) {
        pResponse->autorelease();
        return pResponse;
    }
    CC_SAFE_RELEASE(pResponse);
    return nullptr;
}

bool MWNetResponse::init(const std::string &protocolId, MWBinaryData *body, MWNetRequest *request)
{
    if (protocolId.size() <= 0 || !body->isValid()) {
        return false;
    }
    
    _protocolId = protocolId;
    _body = body;
    _relatedRequest = request;
	CC_SAFE_RETAIN(_relatedRequest);
    
    return true;
}

MWNetResponse::~MWNetResponse()
{
    CC_SAFE_RELEASE(_relatedRequest);
}

MW_FRAMEWORK_END