//
//  TestSvgViewController.cpp
//  GameFramework
//
//  Created by Xin Wan on 5/7/15.
//
//

#include "TestSvgViewController.h"

#include "cocos2d.h"

using namespace mwframework;
using namespace cocos2d;

TestSvgViewController *TestSvgViewController::create()
{
    auto pRet = new TestSvgViewController();
    if (pRet && pRet->init(nullptr)) {
        pRet->autorelease();
        return pRet;
    }
    return nullptr;
}

TestSvgViewController::TestSvgViewController()
{
    
}

void TestSvgViewController::viewDidLoad()
{
    MWViewController::viewDidLoad();
    
    auto pSvg = mwframework::MWSvgSprite::createWithFile("res/tiger.svg", 111111);
    pSvg->setVectorScale(2.0f);
    pSvg->setPosition(Director::getInstance()->getWinSize().width * 0.5, Director::getInstance()->getWinSize().height * 0.5);
    _view->addChild(pSvg);
}

void TestSvgViewController::viewDidUnload()
{
    MWViewController::viewDidUnload();
}