/******************************
 Description: GIF sprite.
 Author: M.Wan
 Date: 4/14/2015
 ******************************/

#ifndef __TEXTURE_GIF_GIF_SPRITE__
#define __TEXTURE_GIF_GIF_SPRITE__

#include "../../base/mwbase.h"
#include "cocos2d.h"
#include <string>

MW_FRAMEWORK_BEGIN

class MWGifFrame;

/**
 * GIF sprite.
 */
class MW_DLL MWGifSprite : public cocos2d::Sprite
{
public:
    /**
     * Create gif sprite by a gif image path.
     *
     * @param gifPath GIF file path.
     */
    static MWGifSprite *createWithFile(const std::string &gifPath);
    /**
     * Create gif sprite with binary data.
     *
     * @param imgData GIF binary data.
     */
    static MWGifSprite *createWithRawData(MWBinaryData *imgData);
    
    /**
     * GIF sprite destructor.
     */
    virtual ~MWGifSprite();
    
    inline MWArrayList *getFrames()
    {
        return _gifFrames;
    }
    cocos2d::SpriteFrame *getSpriteFrameAtIndex(int index);
    
    /**
     * Play the animation.
     *
     * @param count How many times would you want to play the animation? It will play forever if the count is set to 0.
     */
    void play(MW_UINT count = 0);
    /**
     * Pause the animation.
     */
    void pause();
    /**
     * Resume the animation.
     */
    void resume();
    /**
     * Stop the animation, the sprite will display the first texture.
     */
    void stop();
    
    virtual void update(float dt) override;
    
    MW_SYNTHESIZE(float, _speedRatio, SpeedRatio);
    
protected:
    bool initWithFile(const std::string &gifPath);
    bool initWithRawData(MWBinaryData *imgData);
    
    MWGifSprite();
    
    MWGifFrame *generateFrameAtIndex(int index);
    bool openGif(MW_RAW_DATA imgData);
    
    MW_UINT getTotalDuration();
    float getUnitDeltaTime();
    cocos2d::Texture2D *createTextureByRawData(MW_RAW_DATA imgData);
    MWGifFrame *createGifFrame(cocos2d::Texture2D *texture, MW_UINT duration);
    
    MWArrayList *_gifFrames;
    
    int _currentIndex;
    double _passedDeltaTime;
    MW_UINT _repeatTimes;
    MW_UINT _playTimes;
    bool _playing;
};

MW_FRAMEWORK_END

#endif /* defined(__TEXTURE_GIF_GIF_SPRITE__) */
