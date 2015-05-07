//
//  TestZipViewController.cpp
//  GameFramework
//
//  Created by Xin Wan on 5/7/15.
//
//

#include "TestZipViewController.h"

#include "cocos2d.h"

using namespace mwframework;
using namespace cocos2d;

TestZipViewController *TestZipViewController::create()
{
    auto pRet = new TestZipViewController();
    if (pRet && pRet->init(nullptr)) {
        pRet->autorelease();
        return pRet;
    }
    return nullptr;
}

TestZipViewController::TestZipViewController()
{
    
}

void TestZipViewController::viewDidLoad()
{
    MWViewController::viewDidLoad();
    
    auto newZip = mwframework::MWZipData::createWithNewFile("res/temp.zip");
    newZip->beginZip();
    newZip->zipNewFile("aaa.gif", mwframework::MWIOUtils::getInstance()->getDataFromFile("res/GIF/150.gif"));
    newZip->endZip();
    newZip->beginUnzip();
    auto newData = newZip->getCompressedFileData("aaa.gif");
    newZip->endUnzip();
    auto pNewGif = mwframework::MWGifSprite::createWithRawData(newData);
    pNewGif->setScale(2.5f, 2.5f);
    pNewGif->setPosition(Director::getInstance()->getWinSize().width * 0.5, Director::getInstance()->getWinSize().height * 0.5);
    _view->addChild(pNewGif);
}

void TestZipViewController::viewDidUnload()
{
    MWViewController::viewDidUnload();
}