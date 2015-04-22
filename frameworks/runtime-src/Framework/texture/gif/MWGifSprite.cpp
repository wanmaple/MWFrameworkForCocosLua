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
    if (!Sprite::init()) {
        return false;
    }
    if (!this->openGif(imgData->getData())) {
        return false;
    }
    if (g_hGif->ImageCount <= 0) {
        return false;
    }
    _gifFrames = new MWArrayList();
    MWGifFrame *pFrame = nullptr;
    for (int i = 0; i < g_hGif->ImageCount; ++i) {
        pFrame = this->getFrameAtIndex(i);
        if (pFrame) {
            _gifFrames->appendObject(pFrame);
        }
        _gifFrames->appendObject(pFrame);
    }

    this->setSpriteFrame(static_cast<MWGifFrame *>(_gifFrames->objectAtIndex(0))->getSpriteFrame());
    
    this->play();
    
    return true;
}

MWGifSprite::MWGifSprite()
: Sprite()
, _gifFrames(nullptr)
, _currentIndex(0)
, _passedDeltaTime(0.0f)
, _repeatTimes(0)
, _playTimes(0)
, _playing(false)
{
    
}

MWGifSprite::~MWGifSprite()
{
    CC_SAFE_RELEASE(_gifFrames);
    if (g_hGif) {
        int err;
        DGifCloseFile(g_hGif, &err);
    }
}

void MWGifSprite::play(MW_UINT count)
{
    if (_playing) {
        return;
    }
    _repeatTimes = count;
    _playing = true;
    Director::getInstance()->getScheduler()->scheduleUpdate(this, 0, false);
}

void MWGifSprite::pause()
{
    _playing = false;
}

void MWGifSprite::resume()
{
    _playing = true;
}

void MWGifSprite::stop()
{
    Director::getInstance()->getScheduler()->unscheduleUpdate(this);
    _currentIndex = 0;
    _passedDeltaTime = 0.0f;
    _repeatTimes = 0;
    _playTimes = 0;
    _playing = false;
    this->setSpriteFrame(static_cast<MWGifFrame *>(_gifFrames->objectAtIndex(0))->getSpriteFrame());
}

void MWGifSprite::update(float dt)
{
    // paused.
    if (!_playing) {
        return;
    }
    
    _passedDeltaTime += dt;
    MWGifFrame *pFrame = static_cast<MWGifFrame *>(_gifFrames->objectAtIndex(_currentIndex));
    MW_UINT duration = pFrame->getDuration();
    if (_passedDeltaTime * 1000 > duration) {
        _passedDeltaTime -= (double)duration / 1000;
        // update frame
        ++_currentIndex;
        if (_currentIndex >= _gifFrames->count()) {
            ++_playTimes;
            // repeat forever? reach the repeat times?
            if (_repeatTimes > 0 && _playTimes >= _repeatTimes) {
                this->stop();
                return;
            }
            _currentIndex = 0;
        }
        pFrame = static_cast<MWGifFrame *>(_gifFrames->objectAtIndex(_currentIndex));
        this->setSpriteFrame(pFrame->getSpriteFrame());
    }
}

MW_UINT MWGifSprite::getTotalDuration()
{
    static MW_UINT totalDuration = 0;
    if (totalDuration > 0) {
        return totalDuration;
    }
    for (int i = 0; i < _gifFrames->count(); ++i) {
        MWGifFrame *pFrame = static_cast<MWGifFrame *>(_gifFrames->objectAtIndex(i));
        totalDuration += pFrame->getDuration();
    }
    return totalDuration;
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

MWGifFrame *MWGifSprite::getFrameAtIndex(int i)
{
    // gif width and height
    int bgWidth = g_hGif->SWidth;
    int bgHeight = g_hGif->SHeight;
    // check bg color, if the global color map is nonexistent, then the bg color is no use.
    GifColorType defaultColor = { 0x0, 0x0, 0x0 };
    GifColorType bgColor = g_hGif->SColorMap ? g_hGif->SColorMap->Colors[g_hGif->SBackGroundColor] : defaultColor;
    // alloc the data for the bg at first, use RGBA8888 here
    MW_UINT len = bgWidth * bgHeight * sizeof(MW_UINT);
    unsigned int *pBgBuffer = (unsigned int*)malloc(len);
    // fill the bg color to the bg buffer
    // the first row
    unsigned int r, g, b, a;
    r = bgColor.Red;
    g = bgColor.Green;
    b = bgColor.Blue;
    a = 0x0;       // alpha, 0 indicates transparency
    unsigned int bgRgba = (a << 24) | (b << 16) | (g << 8) | r;
    for (int i = 0; i < bgWidth; ++i) {
        pBgBuffer[i] = bgRgba;
    }
    // copy the first row to the rest rows.
    for (int i = 1; i < bgHeight; ++i) {
        memcpy(pBgBuffer + i * bgWidth, pBgBuffer, bgWidth);
    }
    
    // save the sub image
    unsigned int *pImgBuffer = nullptr;
    pImgBuffer = (unsigned int*)malloc(len);
    memcpy(pImgBuffer, pBgBuffer, len);
    
    int top = g_hGif->SavedImages[i].ImageDesc.Top;
    int left = g_hGif->SavedImages[i].ImageDesc.Left;
    int width = g_hGif->SavedImages[i].ImageDesc.Width;
    int height = g_hGif->SavedImages[i].ImageDesc.Height;
    // check transparency from extension blocks
    GraphicsControlBlock gcb;
    DGifSavedExtensionToGCB(g_hGif, i, &gcb);
//    CCLOG("delay ts: %d", gcb.DelayTime);
    // image raw data: RGBRGB...(all color index) read them one by one
    MW_BYTE *pRawData = g_hGif->SavedImages[i].RasterBits;
    // check local color map, if nonexistence, use global color map
    // any possibility that neither of color maps exists?
    GifColorType *pColorMap = g_hGif->SavedImages[i].ImageDesc.ColorMap ? g_hGif->SavedImages[i].ImageDesc.ColorMap->Colors : g_hGif->SColorMap->Colors;
    // calculate the offset, retrieve data from raw data
    MW_UINT *pImgPtr = pImgBuffer + top * bgWidth + left;
    MW_BYTE *pRawPtr = pRawData;
    int rawIndex;
    GifColorType color;
    for (int y = 0; y < height; ++y) {
        for (int x = 0; x < width; ++x) {
            rawIndex = pRawPtr[x];
            // check whether it is the transparent pixel
            if (gcb.TransparentColor != -1 && gcb.TransparentColor == rawIndex) {
                // skip the current pixel.
                continue;
            }
            color = pColorMap[rawIndex];
            r = color.Red;
            g = color.Green;
            b = color.Blue;
            a = 0xff;       // alpha, default as 100% opacity
            pImgPtr[x] = (a << 24) | (b << 16) | (g << 8) | r;
        }
        // shift the pointer
        pImgPtr += width + left;
        pRawPtr += width;
    }
    
    // get duration
    MW_UINT duration = 0;
    for (int n = 0; n <= i; ++n) {
        duration += this->getDurationAtIndex(n);
    }
    
    // create texture
    auto pTexture = new Texture2D();
    pTexture->initWithData((MW_RAW_DATA)pImgBuffer, len, Texture2D::PixelFormat::RGBA8888, bgWidth, bgHeight, Size(bgWidth, bgHeight));
    pTexture->autorelease();
    free(pImgBuffer);
    auto pSpriteFrame = SpriteFrame::createWithTexture(pTexture, Rect(0, 0, pTexture->getContentSize().width, pTexture->getContentSize().height));
    
    // clean the buffer
    free(pBgBuffer);
    MWGifFrame *pFrame = MWGifFrame::create(pSpriteFrame, duration);
    
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
            duration = ((b[2] << 8) | b[1]);
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