#include "MWGifSprite.h"

#include "MWGifFrame.h"
#include "gif_lib/gif_lib.h"
#include <new>

#define GIF_DEFAULT_FRAME_UNIT_TIMES 100

using namespace cocos2d;
using namespace std;

MW_FRAMEWORK_BEGIN

/** Global helper attributes and functions **/
static GifFileType *g_hGif = nullptr;
static MW_UINT *g_buffer = nullptr;
static MW_UINT *g_backUp = nullptr;
static int g_currentIndex = -1;
static int g_lastDrawIndex = -1;
static bool g_bgColorInited = false;

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

static MW_UINT GetBackgroundColor()
{
    static MW_UINT bgRgba;
    if (g_bgColorInited) {
        return bgRgba;
    }
    // check bg color, if the global color map is nonexistent, then the bg color is no use.
    GifColorType defaultColor = { 0x0, 0x0, 0x0 };
    GifColorType bgColor = g_hGif->SColorMap ? g_hGif->SColorMap->Colors[g_hGif->SBackGroundColor] : defaultColor;
    // convert to RGBA8888 format.
    MW_UINT r, g, b, a;
    r = bgColor.Red;
    g = bgColor.Green;
    b = bgColor.Blue;
    a = 0xff;
    bgRgba = (a << 24) | (b << 16) | (g << 8) | r;
    
    return bgRgba;
}

static void ClearWithBackgroundColor(MW_UINT *buffer)
{
    int bgWidth = g_hGif->SWidth;
    int bgHeight = g_hGif->SHeight;
    MW_UINT bgRgba = GetBackgroundColor();
    
    // first row.
    for (int i = 0; i < bgWidth; ++i) {
        buffer[i] = bgRgba;
    }
    // copy the first row to the rest rows.
    for (int i = 1; i < bgHeight; ++i) {
        memcpy(buffer + i * bgWidth, buffer, bgWidth);
    }
}

static void ClearRectWithColor(MW_UINT *buffer, int left, int top, int width, int height, MW_UINT color)
{
    int bgWidth = g_hGif->SWidth;
    MW_UINT *pDstPtr = buffer + top * bgWidth + left;
    for (int y = 0; y < height; ++y) {
        for (int x = 0; x < width; ++x) {
            pDstPtr[x] = color;
        }
        // shift the pointer
        pDstPtr += bgWidth;
    }
}

static MW_UINT GetDuration(const SavedImage *img)
{
    // get the duration at the specified gif image.
    MW_UINT duration = 0;
    ExtensionBlock *pEb = nullptr;
    for (int i = 0; i < img->ExtensionBlockCount; ++i) {
        pEb = img->ExtensionBlocks + i;
        if (pEb->Function == GRAPHICS_EXT_FUNC_CODE) {
            int size = img->ExtensionBlocks[i].ByteCount;
            if (size < 4) {
                break;
            }
            const MW_BYTE *b = (const MW_BYTE *)img->ExtensionBlocks[i].Bytes;
            duration = ((b[2] << 8) | b[1]);
            break;
        }
    }
    
    return duration;
}

static void GetTransparencyAndDisposal(const SavedImage *img, bool *isTransparent, int *disposal)
{
    *isTransparent = false;
    *disposal = 0;
    ExtensionBlock *pEb = nullptr;
    for (int i = 0; i < img->ExtensionBlockCount; ++i) {
        pEb = img->ExtensionBlocks + i;
        if (pEb->Function == GRAPHICS_EXT_FUNC_CODE && pEb->ByteCount == 4) {
            *isTransparent = (pEb->Bytes[0] & 0x1) == 1;
            *disposal = (pEb->Bytes[0] >> 2) & 0x7;
        }
    }
}

// check if the covered image is completely covered by target image.
static bool CheckWhetherCovered(const SavedImage *targetImg, const SavedImage *coveredImg)
{
    if (targetImg->ImageDesc.Left <= coveredImg->ImageDesc.Left && coveredImg->ImageDesc.Left + coveredImg->ImageDesc.Width <= targetImg->ImageDesc.Left + targetImg->ImageDesc.Width && targetImg->ImageDesc.Top <= coveredImg->ImageDesc.Top && coveredImg->ImageDesc.Top + coveredImg->ImageDesc.Height <= targetImg->ImageDesc.Top + targetImg->ImageDesc.Height) {
        return true;
    }
    return false;
}

static void DisposeFrame(const SavedImage *currentImg, const SavedImage *nextImg, MW_UINT bgColor)
{
    // we can skip the disposal process if next frame is not transparent and cover the current area completely.
    bool isCurrentTransparent;
    int currentDisposal;
    GetTransparencyAndDisposal(currentImg, &isCurrentTransparent, &currentDisposal);
    bool isNextTransparent;
    int nextDisposal;
    GetTransparencyAndDisposal(nextImg, &isNextTransparent, &nextDisposal);
    
    // 0       /* No disposal specified. */
    // 1       /* Leave image in place */
    // 2       /* Set area to background color */
    // 3       /* Restore to previous content */
    if ((currentDisposal == 2 || currentDisposal == 3) && (isNextTransparent || !CheckWhetherCovered(nextImg, currentImg))) {
        if (currentDisposal == 2) {
            // restore.
            ClearRectWithColor(g_buffer, currentImg->ImageDesc.Left, currentImg->ImageDesc.Top, currentImg->ImageDesc.Width, currentImg->ImageDesc.Height, bgColor);
        } else if (currentDisposal == 3) {
            // swap from the back up.
            MW_UINT *pTmp = g_buffer;
            g_buffer = g_backUp;
            g_backUp = pTmp;
        }
    }
    
    // save current image if the disposal of next frame is 3.
    if (nextDisposal == 3) {
        int bgWidth = g_hGif->SWidth;
        int bgHeight = g_hGif->SHeight;
        MW_UINT len = bgWidth * bgHeight * sizeof(MW_UINT);
        memcpy(g_backUp, g_buffer, len);
    }
}

static bool CheckWhetherWillBeCleared(const SavedImage *img)
{
    ExtensionBlock *pEb = nullptr;
    for (int i = 0; i < img->ExtensionBlockCount; ++i) {
        pEb = img->ExtensionBlocks + i;
        if (pEb->Function == GRAPHICS_EXT_FUNC_CODE && pEb->ByteCount == 4) {
            int disposal = (pEb->Bytes[0] >> 2) & 0x7;
            if (disposal == 2 || disposal == 3) {
                return true;
            }
        }
    }
    
    return false;
}


static void DrawFrame(MW_UINT *buffer, const SavedImage *img, const ColorMapObject *colorMap)
{
    // find transparency index.
    int transparentIndex = -1;
    ExtensionBlock *pEb = nullptr;
    for (int i = 0; i < img->ExtensionBlockCount; ++i) {
        pEb = img->ExtensionBlocks + i;
        if (pEb->Function == GRAPHICS_EXT_FUNC_CODE && pEb->ByteCount == 4) {
            bool isTransparent = (pEb->Bytes[0] & 0x1) == 1;
            if (isTransparent) {
                transparentIndex = (MW_BYTE)pEb->Bytes[3];
            }
        }
    }
    
    // check local color map, if nonexistence, use global color map
    if (img->ImageDesc.ColorMap) {
        colorMap = img->ImageDesc.ColorMap;
    }
    
    // any possibility that neither of color maps exists?
    if (!colorMap || colorMap->ColorCount != (1 << colorMap->BitsPerPixel)) {
        return;
    }
    
    // draw.
    int bgWidth = g_hGif->SWidth;
    int top = img->ImageDesc.Top;
    int left = img->ImageDesc.Left;
    int width = img->ImageDesc.Width;
    int height = img->ImageDesc.Height;
    MW_BYTE *pRawData = img->RasterBits;
    // calculate the offset, retrieve data from raw data
    MW_UINT *pImgPtr = g_buffer + top * bgWidth + left;
    MW_BYTE *pRawPtr = pRawData;
    int rawIndex;
    GifColorType *pColorMap = colorMap->Colors;
    GifColorType color;
    MW_UINT r, g, b, a;
    for (int y = 0; y < height; ++y) {
        for (int x = 0; x < width; ++x) {
            rawIndex = pRawPtr[x];
            // check whether it is the transparent pixel
            if (transparentIndex > 0 && transparentIndex == rawIndex) {
                // skip the current pixel.
                continue;
            }
            color = pColorMap[rawIndex];
            r = color.Red;
            g = color.Green;
            b = color.Blue;
            a = 0xff;
            pImgPtr[x] = (a << 24) | (b << 16) | (g << 8) | r;
        }
        // shift the pointer
        pImgPtr += bgWidth;
        pRawPtr += width;
    }
}



/** MWGifSprite implementation **/
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
        pFrame = this->generateFrameAtIndex(i);
        if (pFrame) {
            _gifFrames->appendObject(pFrame);
        }
    }
    
    // clean the buffer
    if (g_buffer) {
        free(g_buffer);
        g_buffer = nullptr;
    }
    if (g_backUp) {
        free(g_backUp);
        g_backUp = nullptr;
    }
    g_currentIndex = g_lastDrawIndex = -1;
    g_bgColorInited = false;
    // close gif
    int err;
    DGifCloseFile(g_hGif, &err);
    g_hGif = nullptr;

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
, _speedRatio(1.0f)
{
    
}

MWGifSprite::~MWGifSprite()
{
    CC_SAFE_RELEASE(_gifFrames);
    if (g_hGif) {
        int err;
        DGifCloseFile(g_hGif, &err);
    }
    if (g_buffer) {
        free(g_buffer);
        g_buffer = nullptr;
    }
    if (g_backUp) {
        free(g_backUp);
        g_backUp = nullptr;
    }
}

SpriteFrame *MWGifSprite::getSpriteFrameAtIndex(int index)
{
    MWGifFrame *pFrame = static_cast<MWGifFrame *>(_gifFrames->objectAtIndex(index));
    return pFrame->getSpriteFrame();
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
    if (_passedDeltaTime * this->getUnitDeltaTime() > duration) {
        _passedDeltaTime -= (double)duration / this->getUnitDeltaTime();
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

float MWGifSprite::getUnitDeltaTime()
{
    return GIF_DEFAULT_FRAME_UNIT_TIMES * this->_speedRatio;
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

MWGifFrame *MWGifSprite::generateFrameAtIndex(int i)
{
    if (!g_hGif || i < 0 || i >= g_hGif->ImageCount) {
        return nullptr;
    }
    
    // duration
    MW_UINT duration = GetDuration(&g_hGif->SavedImages[i]);
    g_currentIndex = i;
    
    // gif width and height
    int bgWidth = g_hGif->SWidth;
    int bgHeight = g_hGif->SHeight;
    if (bgWidth <= 0 || bgHeight <= 0) {
        return nullptr;
    }
    
    if (g_lastDrawIndex >= 0 && g_lastDrawIndex == g_currentIndex) {
        return this->createGifFrame(this->createTextureByRawData(g_buffer), duration);
    }
    
    int startIndex = g_lastDrawIndex + 1;
    if (g_lastDrawIndex < 0 || !g_buffer) {
        // first time, do initialization.
        MW_UINT len = bgWidth * bgHeight * sizeof(MW_UINT);
        // RGBA8888 format.
        g_buffer = (unsigned int *) malloc(len);
        g_backUp = (unsigned int *) malloc(len);
        startIndex = 0;
    } else if (startIndex > g_currentIndex) {
        // rewind to first frame for repeat.
        startIndex = 0;
    }
    
    int lastIndex = g_currentIndex;
    if (lastIndex < 0) {
        // first time
        lastIndex = 0;
    } else if (lastIndex > g_hGif->ImageCount - 1) {
        // this block must not be reached.
        lastIndex = g_hGif->ImageCount - 1;
    }
    
    bool tran;
    int tmpDisposal;
    GetTransparencyAndDisposal(&g_hGif->SavedImages[i], &tran, &tmpDisposal);
    CCLOG("%d", tmpDisposal);
    
    // get bg color.
    static MW_UINT paintColor;
    // draw each frame, not an intelligent way.
    for (int i = startIndex; i <= lastIndex; ++i) {
        const SavedImage *pImg = &g_hGif->SavedImages[i];
        if (i == 0) {
            bool isTransparent;
            int disposal;
            GetTransparencyAndDisposal(pImg, &isTransparent, &disposal);
            if (!isTransparent && g_hGif->SColorMap) {
                paintColor = GetBackgroundColor();
            }
            // clear with bg color.
            ClearWithBackgroundColor(g_buffer);
            ClearWithBackgroundColor(g_backUp);
        } else {
            // dispose previous frame before move to next frame.
            const SavedImage *pPrev = &g_hGif->SavedImages[i - 1];
            DisposeFrame(pImg, pPrev, paintColor);
        }
        
        // we can skip this process if the current index is not the last and disposal method is 2 or 3.
        if (i == lastIndex || !CheckWhetherWillBeCleared(pImg)) {
            // draw frame.
            DrawFrame(g_buffer, pImg, g_hGif->SColorMap);
        }
    }
    
    // save last index
    g_lastDrawIndex = lastIndex;
    
    // create texture
    auto pTexture = this->createTextureByRawData(g_buffer);
    auto pFrame = this->createGifFrame(pTexture, duration);
    
    return pFrame;
}

Texture2D *MWGifSprite::createTextureByRawData(void *imgData)
{
    int bgWidth = g_hGif->SWidth;
    int bgHeight = g_hGif->SHeight;
    int len = bgWidth * bgHeight * sizeof(MW_UINT);
    auto pTexture = new Texture2D();
    pTexture->initWithData(imgData, len, Texture2D::PixelFormat::RGBA8888, bgWidth, bgHeight, Size(bgWidth, bgHeight));
    pTexture->autorelease();
    
    return pTexture;
}

MWGifFrame *MWGifSprite::createGifFrame(cocos2d::Texture2D *texture, unsigned int duration)
{
    auto pSpriteFrame = SpriteFrame::createWithTexture(texture, Rect(0, 0, texture->getContentSize().width, texture->getContentSize().height));
    MWGifFrame *pFrame = MWGifFrame::create(pSpriteFrame, duration);
    
    return pFrame;
}

MW_FRAMEWORK_END