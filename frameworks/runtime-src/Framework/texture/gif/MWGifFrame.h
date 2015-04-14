/******************************
 Description: GIF frame data.
 Author: M.Wan
 Date: 4/14/2015
 ******************************/

#ifndef __TEXTURE_GIF_GIF_FRAME__
#define __TEXTURE_GIF_GIF_FRAME__

#include "../../base/mwbase.h"
#include "cocos2d.h"

MW_FRAMEWORK_BEGIN

struct ColorRGBA
{
    MW_BYTE r;
    MW_BYTE g;
    MW_BYTE b;
    MW_BYTE a;
};

class MWBitmap
{
public:
    explicit MWBitmap(MW_UINT width, MW_UINT height);
    ~MWBitmap();
    
    void allocate();
    void destroy();
    
    bool isValid();
    
    void clearWithColor(const ColorRGBA &color);
    
    ColorRGBA *offsetAt(int left, int top);
    
    MW_SYNTHESIZE(MW_UINT, _width, Width);
    MW_SYNTHESIZE(MW_UINT, _height, Height);
    MW_SYNTHESIZE_READONLY(ColorRGBA *, _data, Data);
};

/**
 * GIF frame wrapper.
 */
class MW_DLL MWGifFrame : public MWObject, public IUninheritable<MWGifFrame>
{
    friend class MWGifSprite;
public:
    /**
     * Create a wrapper of gif frame data.
     */
    static MWGifFrame *create(cocos2d::Texture2D *texture, MW_UINT duration);
    
    ~MWGifFrame();
    
    MW_SYNTHESIZE(MW_UINT, _duration, Duration);
//    MW_SYNTHESIZE_READONLY(MW_UINT, _index, Index);
    
    /**
     * Texture getter and setter.
     */
    inline cocos2d::Texture2D *getTexture()
    {
        return _texture;
    }
    void setTexture(cocos2d::Texture2D *texture) MW_NOEXCEPTION(MW_WHETHER_THROW_EXCEPTION);
    
protected:
    bool init(cocos2d::Texture2D *texture, MW_UINT duration);
    
    cocos2d::Texture2D *_texture;
};

MW_FRAMEWORK_END

#endif /* defined(__TEXTURE_GIF_GIF_FRAME__) */
