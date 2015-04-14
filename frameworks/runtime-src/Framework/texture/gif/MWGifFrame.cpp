#include "MWGifFrame.h"

#include <new>

using namespace cocos2d;
using namespace std;

MW_FRAMEWORK_BEGIN

MWBitmap::MWBitmap(MW_UINT width, MW_UINT height)
: _width(width)
, _height(height)
{
}

MWBitmap::~MWBitmap()
{
    this->destroy();
}

void MWBitmap::allocate()
{
    CCASSERT(!_data && _width * _height > 0, "Invalid bitmap data.");
    _data = (ColorRGBA *)malloc(_width * _height * sizeof(ColorRGBA));
}

void MWBitmap::destroy()
{
    if (_data) {
        free(_data);
        _data = nullptr;
    }
}

bool MWBitmap::isValid()
{
    return _width * _height > 0 && _data;
}

void MWBitmap::clearWithColor(const mwframework::ColorRGBA &color)
{
    ColorRGBA paintColor = color;
    
    // make rgb premultiplied
    if (color.a != 255) {
        paintColor.r = ALPHA_MUL(color.r, color.a);
        paintColor.g = ALPHA_MUL(color.g, color.a);
        paintColor.b = ALPHA_MUL(color.b, color.a);
    }
    
    for (MW_UINT i = 0; i < _width * _height; ++i) {
        *(_data + i) = paintColor;
    }
}

ColorRGBA *MWBitmap::offsetAt(int left, int top)
{
    return _data + top * _width + left;
}



MWGifFrame *MWGifFrame::create(Texture2D *texture, MW_UINT duration)
{
    auto pRet = new (nothrow) MWGifFrame();
    if (pRet && pRet->init(texture, duration)) {
        pRet->autorelease();
        return pRet;
    }
    CC_SAFE_RELEASE(pRet);
    return nullptr;
}

bool MWGifFrame::init(Texture2D *texture, MW_UINT duration)
{
    if (!_texture) {
        return false;
    }
    _texture = texture;
    CC_SAFE_RETAIN(_texture);
    _duration = duration;
    
    return true;
}

MWGifFrame::~MWGifFrame()
{
    CC_SAFE_RELEASE(_texture);
}

void MWGifFrame::setTexture(Texture2D *texture) MW_NOEXCEPTION(MW_WHETHER_THROW_EXCEPTION)
{
    if (!texture) {
        MW_THROW_EXCEPTION(1006);
    }
    CC_SAFE_RELEASE(_texture);
    _texture = texture;
    CC_SAFE_RETAIN(_texture);
}

MW_FRAMEWORK_END