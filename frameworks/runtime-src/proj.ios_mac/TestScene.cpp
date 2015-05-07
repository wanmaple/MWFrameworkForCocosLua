//
//  TestScene.cpp
//  GameFramework
//
//  Created by Xin Wan on 5/7/15.
//
//

#include "TestScene.h"

#include "TestGifViewController.h"
#include "TestZipViewController.h"
#include "TestSvgViewController.h"
#include "TestHttpViewController.h"

using namespace mwframework;

TestScene *TestScene::create()
{
    auto pScene = new TestScene();
    if (pScene && pScene->_init()) {
        pScene->autorelease();
        return pScene;
    }
    CC_SAFE_RELEASE(pScene);
    return nullptr;
}

TestScene::TestScene()
{
    
}

bool TestScene::_init()
{
    if (!MWGameScene::init()) {
        return false;
    }
    
//    auto pVc = TestGifViewController::create();
//    this->loadViewController(pVc, "TEST_GIF");
//    auto pVc2 = TestZipViewController::create();
//    this->loadViewController(pVc2, "TEST_ZIP");
//    auto pVc3 = TestSvgViewController::create();
//    this->loadViewController(pVc3, "TEST_SVG");
    auto pVc4 = TestHttpViewController::create();
    this->loadViewController(pVc4, "TEST_HTTP");
    
    return true;
}