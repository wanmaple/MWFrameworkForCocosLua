//
//  TestHttpViewController.cpp
//  GameFramework
//
//  Created by Xin Wan on 5/7/15.
//
//

#include "TestHttpViewController.h"

#include "cocos2d.h"

#include <map>
#include <string>

using namespace mwframework;
using namespace cocos2d;
using namespace std;

class JsonHttpTransferStrategy : public IHttpTransferStrategy
{
public:
    std::map<std::string, std::string> transferParameters(const std::string &body) override
    {
        MWJsonObject *pJson = MWJsonObject::createWithString(body);
        map<string, string> params;
        if (pJson) {
            auto pKeys = pJson->allKeys();
            for (auto &key : pKeys) {
                MWObject *pObj = pJson->getObject(key);
                params[key] = pObj->toString();
            }
        }
        return params;
    }
};

class LoginHandler : public MWNetHandler
{
public:
    static LoginHandler *create()
    {
        auto pRet = new LoginHandler();
        if (pRet) {
            pRet->autorelease();
            return pRet;
        }
        CC_SAFE_DELETE(pRet);
        return nullptr;
    }
    
    void handleSuccessfulMessage(MWNetResponse *response) override
    {
        CCLOG("response: %s", response->getBody().c_str());
    }
    void handleFailedMessage(MWNetResponse *response) override
    {
        CCLOG("response: %s", response->getBody().c_str());
    }
};

TestHttpViewController *TestHttpViewController::create()
{
    auto pRet = new TestHttpViewController();
    if (pRet && pRet->init(nullptr)) {
        pRet->autorelease();
        return pRet;
    }
    return nullptr;
}

TestHttpViewController::TestHttpViewController()
{
    
}

void TestHttpViewController::viewDidLoad()
{
    MWViewController::viewDidLoad();
    
    // test http get
    auto pHttpGetService = mwframework::MWHttpGetService::create("http://183.131.76.117/parith/App/");
    pHttpGetService->setTransferRule(new JsonHttpTransferStrategy());
    MWNetCenter::getInstance()->addNetService("service_http_get", pHttpGetService);
    
    MWNetCenter::getInstance()->addNetProtocol("login", "service_http_get", LoginHandler::create());
    
    auto pMsg = MWJsonObject::create();
    pMsg->putString("c", "login");
    pMsg->putString("a", "index");
    pMsg->putString("name", "mw1");
    pMsg->putString("pwd", "1");
    auto pRequest = MWNetRequest::create("login", pMsg->toString());
    MWNetCenter::getInstance()->sendMessage(pRequest);
    
    // test http post
    auto pHttpPostService = mwframework::MWHttpPostService::create("http://www.baidu.com");
    pHttpPostService->setTransferRule(new JsonHttpTransferStrategy());
    MWNetCenter::getInstance()->addNetService("service_http_post", pHttpPostService);
    
    MWNetCenter::getInstance()->addNetProtocol("test", "service_http_post", LoginHandler::create());
    
    auto pRequest2 = MWNetRequest::create("test", pMsg->toString());
    MWNetCenter::getInstance()->sendMessage(pRequest2);
    
    auto pBaiduService = mwframework::MWHttpGetService::create("http://www.baidu.com");
    pBaiduService->setTransferRule(new JsonHttpTransferStrategy());
    MWNetCenter::getInstance()->addNetService("baidu", pBaiduService);
    
    MWNetCenter::getInstance()->addNetProtocol("111", "baidu", LoginHandler::create());
    
    auto pRequest3 = MWNetRequest::create("111", "");
    MWNetCenter::getInstance()->sendMessage(pRequest3);
    
    CCLOG("%s\n", MWIOUtils::getInstance()->resourcePath("res/493.gif").c_str());
}

void TestHttpViewController::viewDidUnload()
{
    MWViewController::viewDidUnload();
}