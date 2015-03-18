#include "MWHttpService.h"

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

MWHttpService *MWHttpService::create(const std::string &serviceAddress)
{
    auto pService = new (nothrow) MWHttpService(serviceAddress);
    if (pService && pService->_init(serviceAddress))
    {
        pService->autorelease();
        return pService;
    }
    CC_SAFE_RELEASE(pService);
    return nullptr;
}

bool MWHttpService::_init(const std::string &serviceAddress)
{
    _serviceAddr = serviceAddress;
    
    return true;
}

MWHttpService::MWHttpService(const std::string &serviceAddress)
: _serviceAddr(serviceAddress)
, _strategy(nullptr)
{
}

MWHttpService::~MWHttpService()
{
    CC_SAFE_DELETE(_strategy);
}

void MWHttpService::sendMessage(MWNetRequest *request)
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
    CCLOG("MWHttpService sent: %s", pHttpRequest->getUrl());
    // set callback
    pHttpRequest->setResponseCallback(MW_CALLBACK_2(MWHttpService::onHttpRequestCompleted, this));
    HttpClient::getInstance()->send(pHttpRequest);
    pHttpRequest->release();
}

void MWHttpService::executeCommand(const std::string &cmd, cocos2d::Ref *param)
{
    // Add user commands here.
}

void MWHttpService::onHttpRequestCompleted(HttpClient *client, HttpResponse *response)
{
    HttpRequest *pRelatedRequest = response->getHttpRequest();
    MWNetRequest *pUserRequest = static_cast<MWNetRequest*>(pRelatedRequest->getUserData());
    if (!response->isSucceed())
    {
//        CCLOG("Response failed. Error: %s", response->getErrorBuffer());
        auto pResponse = MWNetResponse::create(pUserRequest->getProtocolId(), response->getErrorBuffer(), pUserRequest);
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

MWHttpForm *MWHttpService::_createForm(const std::string &body)
{
    CCASSERT(_strategy, "A transfer rule is required!");
    std::map<std::string, std::string> params = _strategy->transferParameters();
    // Put parameters to the form.
    MWHttpForm *pForm = MWHttpForm::create();
    for (auto &pair : params) {
        pForm->putParam(pair.first, pair.second);
    }
    
    return pForm;
}

MW_FRAMEWORK_END