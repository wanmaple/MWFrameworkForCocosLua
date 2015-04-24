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
    static MWGifFrame *create(cocos2d::SpriteFrame *spriteFrame, MW_UINT duration);
    
    ~MWGifFrame();
    
    MW_SYNTHESIZE(MW_UINT, _duration, Duration);
    
    /**
     * Sprite frame getter and setter.
     */
    inline cocos2d::SpriteFrame *getSpriteFrame()
    {
        return _spriteFrame;
    }
    void setSpriteFrame(cocos2d::SpriteFrame *spriteFrame) MW_NOEXCEPTION(MW_WHETHER_THROW_EXCEPTION);
    
protected:
    MWGifFrame();
    
    bool init(cocos2d::SpriteFrame *spriteFrame, MW_UINT duration);
    
    cocos2d::SpriteFrame *_spriteFrame;
};

MW_FRAMEWORK_END

#endif /* defined(__TEXTURE_GIF_GIF_FRAME__) */
