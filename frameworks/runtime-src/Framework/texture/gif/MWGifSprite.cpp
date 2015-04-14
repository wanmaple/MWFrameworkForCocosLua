#include "MWGifSprite.h"

#include "MWGifFrame.h"
#include "gif_lib/gif_lib.h"
#include <new>

using namespace cocos2d;
using namespace std;

MW_FRAMEWORK_BEGIN

static GifFileType *g_hGif = nullptr;

static int DecodeGifCallback(GifFileType *hGif, GifByteType *buffer, int size)
{
    // save the raw data to gif userdata.
    char *pRawData = (char *)hGif->UserData;
    memcpy(buffer, pRawData, size);
    // don't forget to shift the pointer, cuz giflib doesn't read all data at once, you have to remember the offset you have read.
    pRawData += size;
    hGif->UserData = (void *)pRawData;
    
    return size;
}

MWGifSprite *MWGifSprite::createWithFile(const std::string &gifPath)
{
    auto pRet = new (nothrow) MWGifSprite();
    if (pRet && pRet->initWithFile(gifPath)) {
        pRet->autorelease();
        return pRet;
    }
    CC_SAFE_RELEASE(pRet);
    return nullptr;
}

bool MWGifSprite::initWithFile(const std::string &gifPath)
{
    Data data = FileUtils::getInstance()->getDataFromFile(FileUtils::getInstance()->fullPathForFilename(gifPath));
    if (!data.getBytes() || data.getSize() <= 0) {
        return false;
    }
    auto pData = MWBinaryData::create(data.getBytes(), data.getSize());
    
    return this->initWithRawData(pData);
}

MWGifSprite *MWGifSprite::createWithRawData(MWBinaryData *imgData)
{
    auto pRet = new (nothrow) MWGifSprite();
    if (pRet && pRet->initWithRawData(imgData)) {
        pRet->autorelease();
        return pRet;
    }
    CC_SAFE_RELEASE(pRet);
    return nullptr;
}

bool MWGifSprite::initWithRawData(MWBinaryData *imgData)
{
    if (!this->openGif(imgData->getData())) {
        return false;
    }
    if (g_hGif->ImageCount <= 0) {
        return false;
    }
    _gifFrames = MWArrayList::create();
    MWGifFrame *pFrame = nullptr;
    for (int i = 0; i < g_hGif->ImageCount; ++i) {
        pFrame = this->getFrameAtIndex(i);
        if (pFrame) {
            _gifFrames->appendObject(pFrame);
        }
    }
    
    return true;
}

bool MWGifSprite::openGif(void *imgData)
{
    int err = 0;
    GifFileType *hGif = DGifOpen(imgData, DecodeGifCallback, &err);
    if (err) {
        CCLOG("Read gif error.");
        return false;
    }
    if (DGifSlurp(hGif) != GIF_OK) {
        CCLOG("Slurp gif error.");
        DGifCloseFile(hGif, &err);
        return false;
    }
    g_hGif = hGif;
    
    return true;
}

MWGifFrame *MWGifSprite::getFrameAtIndex(int index)
{
    MW_UINT duration = this->getDurationAtIndex(index);
    
    const int width = g_hGif->SWidth;
    const int height = g_hGif->SHeight;
    if (width <= 0 || height <= 0) {
        return nullptr;
    }
    
    MWBitmap *pBmp = new MWBitmap(width, height);
    pBmp->allocate();
    
    ColorRGBA bgColor = { 0 };
    if (g_hGif->SColorMap) {
        const GifColorType &color = g_hGif->SColorMap->Colors[g_hGif->SBackGroundColor];
        bgColor.a = 0xff;
        bgColor.r = color.Red;
        bgColor.g = color.Green;
        bgColor.b = color.Blue;
    }
    
    static ColorRGBA paintColor;
    SavedImage *pCurImg = &g_hGif->SavedImages[index];
    // whether transparent?
    bool tran = false;
    int disposal;
    for (int i = 0; i < pCurImg->ExtensionBlockCount; ++i) {
        ExtensionBlock *pEb = pCurImg->ExtensionBlocks + i;
        if (pEb->Function == GRAPHICS_EXT_FUNC_CODE && pEb->ByteCount == 4) {
            tran = (pEb->Bytes[0] & 0x1) == 1;
            disposal = (pEb->Bytes[0] >> 2) & 0x111;
        }
    }
    if (!tran && g_hGif->SColorMap) {
        paintColor = bgColor;
    }
    pBmp->clearWithColor(paintColor);
    
    // we can skip this process when it's disposal
    if (!this->checkWhetherWillBeCleared(index)) {
        // draw frame
        int transparent = -1;
        
        for (int i = 0; i < pCurImg->ExtensionBlockCount; ++i) {
            ExtensionBlock *pEb = pCurImg->ExtensionBlocks + i;
            if (pEb->Function == GRAPHICS_EXT_FUNC_CODE && pEb->ByteCount == 4) {
                bool isTransparent = (pEb->Bytes[0] & 0x1) == 1;
                if (isTransparent) {
                    transparent = (MW_BYTE)pEb->Bytes[3];
                }
            }
        }
        
        ColorMapObject *pMap = nullptr;
        if (pCurImg->ImageDesc.ColorMap) {
            // use local color table
            pMap = pCurImg->ImageDesc.ColorMap;
        }
        
        if (pMap && pMap->ColorCount == (1 << pMap->BitsPerPixel)) {
            // blit
            const MW_BYTE *pSrc = (MW_BYTE *)pCurImg->RasterBits;
            ColorRGBA *pDst = pBmp->offsetAt(pCurImg->ImageDesc.Left, pCurImg->ImageDesc.Top);
            
            GifWord copyWidth = pCurImg->ImageDesc.Width;
            if (pCurImg->ImageDesc.Left + copyWidth > width) {
                copyWidth = width - pCurImg->ImageDesc.Left;
            }
            GifWord copyHeight = pCurImg->ImageDesc.Height;
            if (pCurImg->ImageDesc.Top + copyHeight > height) {
                copyHeight = height - pCurImg->ImageDesc.Top;
            }
            
            for ( ; copyHeight > 0; --copyHeight) {
                for ( ; copyWidth > 0; --copyWidth, ++pSrc, ++pDst) {
                    if (*pSrc != transparent) {
                        GifColorType tmp = pMap->Colors[*pSrc];
                        *pDst = { tmp.Red, tmp.Green, tmp.Blue, 0xff };
                    }
                }
                pSrc += pCurImg->ImageDesc.Width;
                pDst += width;
            }
        }
    }
    
    // create texture
    Texture2D *pTex = nullptr;
    Image *pImg = new Image();
    do {
        bool res = true;
        ColorRGBA *pColorData = pBmp->getData();
        res = pImg->initWithImageData((const unsigned char *)pColorData, width * height);
        if (!res) {
            break;
        }
        pTex = new Texture2D();
        res = pTex->initWithImage(pImg);
        if (!res) {
            delete pTex;
            pTex = nullptr;
            break;
        }
        pTex->autorelease();
    } while (0);
    
    if (!pTex) {
        return nullptr;
    }
    MWGifFrame *pFrame = MWGifFrame::create(pTex, this->getDurationAtIndex(index));
    return pFrame;
}

MW_UINT MWGifSprite::getDurationAtIndex(int index)
{
    MW_UINT duration = 0;
    SavedImage img = g_hGif->SavedImages[index];
    for (int i = 0; i < img.ExtensionBlockCount; ++i) {
        if (img.ExtensionBlocks[i].Function == GRAPHICS_EXT_FUNC_CODE) {
            int size = img.ExtensionBlocks[i].ByteCount;
            if (size < 4) {
                break;
            }
            const uint8_t *b = (const uint8_t *)img.ExtensionBlocks[i].Bytes;
            duration = ((b[2] << 8) | b[1]) * 10;
            break;
        }
    }
    
    return duration;
}

bool MWGifSprite::checkWhetherWillBeCleared(int index)
{
    SavedImage img = g_hGif->SavedImages[index];
    for (int i = 0; i < img.ExtensionBlockCount; ++i) {
        ExtensionBlock *pEb = img.ExtensionBlocks + i;
        if (pEb->Function == GRAPHICS_EXT_FUNC_CODE && pEb->ByteCount == 4) {
            // check disposal method
            int disposal = (pEb->Bytes[0] >> 2) & 0x111;
            if (disposal == 2 || disposal == 3) {
                return true;
            }
        }
    }
    return false;
}

MW_FRAMEWORK_END