#include "MWHttpGetService.h"

#include "HttpRequest.h"
#include "MWHttpForm.h"
#include "../MWNetRequest.h"
#include "../MWNetResponse.h"
#include "../MWNetCenter.h"

#include <new>
#include <vector>

using namespace cocos2d;
using namespace cocos2d::network;
using namespace std;

MW_FRAMEWORK_BEGIN

MWHttpGetService *MWHttpGetService::create(const std::string &serviceAddress)
{
    auto pService = new (nothrow) MWHttpGetService(serviceAddress);
    if (pService && pService->_init(serviceAddress))
    {
        pService->autorelease();
        return pService;
    }
    CC_SAFE_RELEASE(pService);
    return nullptr;
}

bool MWHttpGetService::_init(const std::string &serviceAddress)
{
    _serviceAddr = serviceAddress;
    
    return true;
}

MWHttpGetService::MWHttpGetService(const std::string &serviceAddress)
: _serviceAddr(serviceAddress)
, _strategy(nullptr)
{
}

MWHttpGetService::~MWHttpGetService()
{
    CC_SAFE_DELETE(_strategy);
}

void MWHttpGetService::sendMessage(MWNetRequest *request)
{
    std::string body = request->getBody();
    auto pHttpRequest = new HttpRequest();
    // save user data
    pHttpRequest->setUserData(request);
    // need retain
    request->retain();
    pHttpRequest->setRequestType(HttpRequest::Type::GET);
    MWHttpForm *pForm = nullptr;
    // get parameters through the strategy.
    pForm = this->_createForm(body);
    
    if (!pForm)
    {
        CCLOG("Invalid http form.");
        return;
    }
    string url = _serviceAddr;
    string formStr = pForm->toString();
    if (formStr.size() > 0)
    {
        url.append("?").append(formStr);
    }
    pHttpRequest->setUrl(url.c_str());
    CCLOG("MWHttpGetService sent: %s", pHttpRequest->getUrl());
    // set callback
    pHttpRequest->setResponseCallback(MW_CALLBACK_2(MWHttpGetService::onHttpRequestCompleted, this));
    HttpClient::getInstance()->send(pHttpRequest);
    pHttpRequest->release();
}

void MWHttpGetService::executeCommand(const std::string &cmd, cocos2d::Ref *param)
{
    // Add user commands here.
}

void MWHttpGetService::onHttpRequestCompleted(HttpClient *client, HttpResponse *response)
{
    HttpRequest *pRelatedRequest = response->getHttpRequest();
    MWNetRequest *pUserRequest = static_cast<MWNetRequest*>(pRelatedRequest->getUserData());
    if (!response->isSucceed())
    {
//        CCLOG("Response failed. Error: %s", response->getErrorBuffer());
        string error = "unknown error occured.";
        if (response->getErrorBuffer() && strlen(response->getErrorBuffer()) > 0) {
            error = response->getErrorBuffer();
        }
        auto pResponse = MWNetResponse::create(pUserRequest->getProtocolId(), error, pUserRequest);
        MWNetCenter::getInstance()->dispatchFailedMessage(pResponse);
        // retained once when sending request, so release it here.
        pUserRequest->release();
        return;
    }
    // retrieve response data.
    vector<char> *buffer = response->getResponseData();
    string responseBody;
    responseBody.assign(buffer->begin(), buffer->end());
    // please use UTF-8 encoding on server. some decoding may be required. todo
    CCLOG("Response successful. Data: %s", responseBody.c_str());
    // create net response
    auto pResponse = MWNetResponse::create(pUserRequest->getProtocolId(), responseBody, pUserRequest);
    MWNetCenter::getInstance()->dispatchSuccessfulMessage(pResponse);
    // retained once when sending request, so release it here.
    pUserRequest->release();
}

MWHttpForm *MWHttpGetService::_createForm(const std::string &body)
{
    CCASSERT(_strategy, "A transfer rule is required!");
    std::map<std::string, std::string> params = _strategy->transferParameters(body);
    // Put parameters to the form.
    MWHttpForm *pForm = MWHttpForm::create();
    for (auto &pair : params) {
        pForm->putParam(pair.first, pair.second);
    }
    
    return pForm;
}

MW_FRAMEWORK_END