//
//  TestGifViewController.cpp
//  GameFramework
//
//  Created by Xin Wan on 5/7/15.
//
//

#include "TestGifViewController.h"

#include "cocos2d.h"

using namespace mwframework;
using namespace cocos2d;

TestGifViewController *TestGifViewController::create()
{
    auto pRet = new TestGifViewController();
    if (pRet && pRet->init(nullptr)) {
        pRet->autorelease();
        return pRet;
    }
    return nullptr;
}

TestGifViewController::TestGifViewController()
{
    
}

void TestGifViewController::viewDidLoad()
{
    MWViewController::viewDidLoad();
    
    auto pZip = mwframework::MWZipData::createWithExistingFile("res/493.zip");
    pZip->beginUnzip();
    auto pGif = mwframework::MWGifSprite::createWithRawData(pZip->getCompressedFileData("493.gif"));
    pZip->endUnzip();
    pGif->setPosition(Director::getInstance()->getWinSize().width * 0.5, Director::getInstance()->getWinSize().height * 0.5);
    pGif->setSpeedRatio(1.0f);
    pGif->setScale(2.5f, 2.5f);
    _view->addChild(pGif);
    auto pGif2 = mwframework::MWGifSprite::createWithFile("res/GIF/483.gif");
    pGif2->setPosition(Director::getInstance()->getWinSize().width * 0.3, Director::getInstance()->getWinSize().height * 0.3);
    pGif2->setSpeedRatio(1.0f);
    pGif2->setScale(2.5f, 2.5f);
    _view->addChild(pGif2);
    auto pGif3 = mwframework::MWGifSprite::createWithFile("res/GIF/484.gif");
    pGif3->setPosition(Director::getInstance()->getWinSize().width * 0.7, Director::getInstance()->getWinSize().height * 0.3);
    pGif3->setSpeedRatio(1.0f);
    pGif3->setScale(2.5f, 2.5f);
    _view->addChild(pGif3);
    auto gifZip = mwframework::MWZipData::createWithExistingFile("res/GIF/pokemon_gif5.rc");
    gifZip->beginUnzip();
    auto data = gifZip->getCompressedFileData("487_o.gif", "7ujm,lp-");
    gifZip->endUnzip();
    auto pGif4 = mwframework::MWGifSprite::createWithRawData(data);
    pGif4->setPosition(Director::getInstance()->getWinSize().width * 0.5, Director::getInstance()->getWinSize().height * 0.85);
    pGif4->setSpeedRatio(1.0f);
    pGif4->setScale(2.5f, 2.5f);
    _view->addChild(pGif4);
}

void TestGifViewController::viewDidUnload()
{
    MWViewController::viewDidUnload();
}