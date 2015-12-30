#include "MWSvgSprite.h"

#include <stdio.h>
#include <string.h>
#include <float.h>
#define NANOSVG_IMPLEMENTATION
#include "nanosvg/nanosvg.h"
#define NANOSVGRAST_IMPLEMENTATION
#include "nanosvg/nanosvgrast.h"

#include "../../platform/MWIOUtils.h"

#include <new>

using namespace cocos2d;
using namespace std;

MW_FRAMEWORK_BEGIN

typedef struct {
    MW_BYTE r;
    MW_BYTE g;
    MW_BYTE b;
    MW_BYTE a;
} RGBA, *PRGBA, *LPRGBA;

MW_LOCAL NSVGimage *g_nsvgImg = nullptr;
MW_LOCAL NSVGrasterizer *g_nsvgRasterizer = nullptr;

MWSvgSprite *MWSvgSprite::createWithFile(const std::string &svgPath, float dpi)
{
    auto pRet = new (nothrow) MWSvgSprite();
    if (pRet && pRet->initWithFile(svgPath, dpi)) {
        pRet->autorelease();
        return pRet;
    }
    CC_SAFE_RELEASE(pRet);
    return nullptr;
}

bool MWSvgSprite::initWithFile(const std::string &svgPath, float dpi)
{
#if CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID
    Data data = FileUtils::getInstance()->getDataFromFile(svgPath);
    auto pData = MWBinaryData::create(data.getBytes(), data.getSize());
#else
    auto pData = MWIOUtils::getInstance()->getDataFromFile(FileUtils::getInstance()->fullPathForFilename(svgPath));
#endif
    
    return this->initWithRawData(pData, dpi);
}

MWSvgSprite *MWSvgSprite::createWithRawData(mwframework::MWBinaryData *imgData, float dpi)
{
    auto pRet = new (nothrow) MWSvgSprite();
    if (pRet && pRet->initWithRawData(imgData, dpi)) {
        pRet->autorelease();
        return pRet;
    }
    CC_SAFE_RELEASE(pRet);
    return nullptr;
}

bool MWSvgSprite::initWithRawData(mwframework::MWBinaryData *imgData, float dpi)
{
    if (!Sprite::init()) {
        return false;
    }
    
    g_nsvgImg = nsvgParse((char *)imgData->getData(), "px", dpi);
    if (!g_nsvgImg) {
        return false;
    }
    
    auto pTexture = this->getScaledTexture(_vectorScale);
    if (!pTexture) {
        return false;
    }
    
    auto pSpriteFrame = SpriteFrame::createWithTexture(pTexture, Rect(0, 0, pTexture->getContentSize().width, pTexture->getContentSize().height));
    this->setSpriteFrame(pSpriteFrame);
    
    return true;
}

MWSvgSprite::MWSvgSprite()
: _vectorScale(1.0f)
{
    
}

MWSvgSprite::~MWSvgSprite()
{
    if (g_nsvgRasterizer) {
        nsvgDeleteRasterizer(g_nsvgRasterizer);
        g_nsvgRasterizer = nullptr;
    }
    if (g_nsvgImg) {
        nsvgDelete(g_nsvgImg);
        g_nsvgImg = nullptr;
    }
}

void MWSvgSprite::setVectorScale(float scale)
{
    if (_vectorScale != scale) {
        auto pTexture = this->getScaledTexture(scale);
        auto pSpriteFrame = SpriteFrame::createWithTexture(pTexture, Rect(0, 0, pTexture->getContentSize().width, pTexture->getContentSize().height));
        this->setSpriteFrame(pSpriteFrame);
        
        _vectorScale = scale;
    }
}

Texture2D *MWSvgSprite::getScaledTexture(float scale)
{
    int width = g_nsvgImg->width * scale;
    int height = g_nsvgImg->height * scale;
    ssize_t len = width * height * sizeof(RGBA);
    PRGBA pBuffer = (PRGBA) malloc(len);
    
    if (!g_nsvgRasterizer) {
        g_nsvgRasterizer = nsvgCreateRasterizer();
    }
    if (!g_nsvgRasterizer) {
        return nullptr;
    }
    
    nsvgRasterize(g_nsvgRasterizer, g_nsvgImg, 0, 0, scale, (MW_BYTE *) pBuffer, width, height, width * sizeof(RGBA));
    
    auto pTexture = new Texture2D();
    pTexture->initWithData((const MW_RAW_DATA)pBuffer, len, Texture2D::PixelFormat::RGBA8888, width, height, Size(width, height));
    pTexture->autorelease();
    
    return pTexture;
}

MW_FRAMEWORK_END