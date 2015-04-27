#include "MWGifSprite.h"

#include "MWGifFrame.h"
#include "gif_lib/gif_lib.h"
#include <new>

#define GIF_DEFAULT_FRAME_UNIT_TIMES 100

using namespace cocos2d;
using namespace std;

MW_FRAMEWORK_BEGIN

typedef struct {
    MW_BYTE r;
    MW_BYTE g;
    MW_BYTE b;
    MW_BYTE a;
} RGBA, *PRGBA, *LPRGBA;

/** Global helper attributes and functions **/
static GifFileType *g_hGif = nullptr;
static PRGBA g_buffer = nullptr;
static PRGBA g_lastTemplateBuffer = nullptr;
static PRGBA g_lastReserveBuffer = nullptr;
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

static RGBA PackRGBA(MW_BYTE r, MW_BYTE g, MW_BYTE b, MW_BYTE a)
{
    RGBA color;
    color.r = r;
    color.g = g;
    color.b = b;
    color.a = a;
    
    return color;
}

static RGBA GetBackgroundColor()
{
    static RGBA bgRgba;
    if (g_bgColorInited) {
        return bgRgba;
    }
    // check bg color, if the global color map is nonexistent, then the bg color is no use.
    GifColorType defaultColor = { 0x0, 0x0, 0x0 };
    GifColorType bgColor = g_hGif->SColorMap ? g_hGif->SColorMap->Colors[g_hGif->SBackGroundColor] : defaultColor;
    // convert to RGBA8888 format.
    MW_BYTE r, g, b, a;
    r = bgColor.Red;
    g = bgColor.Green;
    b = bgColor.Blue;
    a = 0xff;
    bgRgba = PackRGBA(r, g, b, a);
    CCLOG("BG COLOR: r: %d g: %d b: %d a: %d", r, g, b, a);
    
    return bgRgba;
}

static void ClearWithColor(RGBA *buffer, RGBA color)
{
    int bgWidth = g_hGif->SWidth;
    int bgHeight = g_hGif->SHeight;
    
    // first row.
    for (int i = 0; i < bgWidth; ++i) {
        buffer[i] = color;
    }
    // copy the first row to the rest rows.
    for (int i = 1; i < bgHeight; ++i) {
        memcpy(buffer + i * bgWidth, buffer, bgWidth * sizeof(RGBA));
    }
}

static void ClearRectWithColor(RGBA *buffer, int left, int top, int width, int height, RGBA color)
{
    int bgWidth = g_hGif->SWidth;
    RGBA *pDstPtr = buffer + top * bgWidth + left;
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

static void DrawFrame(RGBA *buffer, const SavedImage *img, const ColorMapObject *colorMap, PRGBA bgColor = nullptr)
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
    RGBA *pImgPtr = g_buffer + top * bgWidth + left;
    MW_BYTE *pRawPtr = pRawData;
    int rawIndex;
    GifColorType *pColorMap = colorMap->Colors;
    GifColorType color;
    CCLOG("Transparent color: r: %d g: %d b: %d", pColorMap[transparentIndex].Red, pColorMap[transparentIndex].Green, pColorMap[transparentIndex].Blue);
    MW_BYTE r, g, b, a;
    for (int y = 0; y < height; ++y) {
        for (int x = 0; x < width; ++x) {
            rawIndex = pRawPtr[x];
            // check whether it is the transparent pixel
            if (transparentIndex >= 0 && transparentIndex == rawIndex) {
                // skip the current pixel.
                if (bgColor) {
                    pImgPtr[x] = *bgColor;
                }
                continue;
            }
            color = pColorMap[rawIndex];
            r = color.Red;
            g = color.Green;
            b = color.Blue;
            a = 0xff;
            pImgPtr[x] = PackRGBA(r, g, b, a);
        }
        // shift the pointer
        pImgPtr += bgWidth;
        pRawPtr += width;
    }
}

static void FreeBuffers()
{
    // clean the buffer
    if (g_buffer) {
        free(g_buffer);
        g_buffer = nullptr;
    }
    if (g_lastTemplateBuffer) {
        free(g_lastTemplateBuffer);
        g_lastTemplateBuffer = nullptr;
    }
    if (g_lastReserveBuffer) {
        free(g_lastReserveBuffer);
        g_lastReserveBuffer = nullptr;
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
    if (!imgData || !imgData->getData() || imgData->getSize() <= 0) {
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
    
    FreeBuffers();
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
    FreeBuffers();
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
    CCLOG("GIF size: %d, %d", g_hGif->SWidth, g_hGif->SHeight);
    
    return true;
}

MWGifFrame *MWGifSprite::generateFrameAtIndex(int index)
{
    if (!g_hGif || index < 0 || index >= g_hGif->ImageCount) {
        return nullptr;
    }
    
    // duration
    MW_UINT duration = GetDuration(&g_hGif->SavedImages[index]);
    
    // gif width and height
    int bgWidth = g_hGif->SWidth;
    int bgHeight = g_hGif->SHeight;
    if (bgWidth <= 0 || bgHeight <= 0) {
        return nullptr;
    }
    
    MW_UINT len = bgWidth * bgHeight * sizeof(MW_UINT);
    if (!g_buffer) {
        // first time, do initialization.
        // RGBA8888 format.
        g_buffer = (PRGBA) malloc(len);
    }
    
    bool tran;
    int tmpDisposal;
    GetTransparencyAndDisposal(&g_hGif->SavedImages[index], &tran, &tmpDisposal);
    GraphicsControlBlock gcb;
    DGifSavedExtensionToGCB(g_hGif, index, &gcb);
    CCLOG("%d\t%d", tmpDisposal, gcb.DisposalMode);
    
    // get bg color.
    RGBA paintColor = GetBackgroundColor();
    const SavedImage *pCurrentImg = &g_hGif->SavedImages[index];
    // check bg transparency.
    bool isCurrentFrameTransparent;
    int currentFrameDisposal;
    GetTransparencyAndDisposal(pCurrentImg, &isCurrentFrameTransparent, &currentFrameDisposal);
    if (isCurrentFrameTransparent) {
        paintColor = { 0 };
    }
    
    if (index == 0) {
        // first time
        // clear with bg color.
        ClearWithColor(g_buffer, paintColor);
        
        // draw frame.
        DrawFrame(g_buffer, pCurrentImg, g_hGif->SColorMap);
    } else {
        const SavedImage *pLastImg = &g_hGif->SavedImages[index - 1];
        bool isLastFrameTransparent;
        int lastFrameDisposal;
        GetTransparencyAndDisposal(pLastImg, &isLastFrameTransparent, &lastFrameDisposal);
        
        // 0       /* No disposal specified. */
        // 1       /* Leave image in place */
        // 2       /* Set area to background color */
        // 3       /* Restore to previous content */
        if (lastFrameDisposal == 0) {
            // won't do any dispose behaviors. just over write the old frame.
            // clear with bg color.
            ClearWithColor(g_buffer, paintColor);
            
            // draw frame.
            DrawFrame(g_buffer, pCurrentImg, g_hGif->SColorMap);
        } else if (lastFrameDisposal == 1) {
            // draw the frame directly on the last frame.
            // draw frame.
            DrawFrame(g_buffer, pCurrentImg, g_hGif->SColorMap);
        } else if (lastFrameDisposal == 2) {
            // use first template image, then draw the frame.
            memcpy(g_buffer, g_lastTemplateBuffer, len);
            // draw frame.
            DrawFrame(g_buffer, pCurrentImg, g_hGif->SColorMap);
        } else if (lastFrameDisposal == 3) {
            // restore to the last reserve image.
            memcpy(g_buffer, g_lastReserveBuffer, len);
            // draw frame.
            DrawFrame(g_buffer, pCurrentImg, g_hGif->SColorMap);
        }
    }
    
    // whether is the disposal template frame.
    if (currentFrameDisposal == 2) {
        if (!g_lastTemplateBuffer) {
            g_lastTemplateBuffer = (PRGBA) malloc(len);
        }
        // save the template
        memcpy(g_lastTemplateBuffer, g_buffer, len);
        ClearRectWithColor(g_lastTemplateBuffer, pCurrentImg->ImageDesc.Left, pCurrentImg->ImageDesc.Top, pCurrentImg->ImageDesc.Width, pCurrentImg->ImageDesc.Height, paintColor);
    }
    
    if (index < g_hGif->ImageCount - 1) {
        bool isNextFrameTransaprent;
        int nextFrameDisposal;
        GetTransparencyAndDisposal(&g_hGif->SavedImages[index + 1], &isNextFrameTransaprent, &nextFrameDisposal);
        
        // whether to reserve the current frame?
        if (currentFrameDisposal != 3 && nextFrameDisposal == 3) {
            // back up the current frame.
            if (!g_lastReserveBuffer) {
                g_lastReserveBuffer = (PRGBA) malloc(len);
            }
            memcpy(g_lastReserveBuffer, g_buffer, len);
        }
    }
    
    // create texture
    auto pTexture = this->createTextureByRawData(g_buffer);
    auto pFrame = this->createGifFrame(pTexture, duration);
    
    return pFrame;
}

Texture2D *MWGifSprite::createTextureByRawData(void *imgData)
{
    int bgWidth = g_hGif->SWidth;
    int bgHeight = g_hGif->SHeight;
    int len = bgWidth * bgHeight * sizeof(RGBA);
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