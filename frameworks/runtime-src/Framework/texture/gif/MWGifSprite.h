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
    
protected:
    bool initWithFile(const std::string &gifPath);
    bool initWithRawData(MWBinaryData *imgData);
    
    MWGifSprite();
    
    bool openGif(MW_RAW_DATA imgData);
    MWGifFrame *getFrameAtIndex(int index);
    MW_UINT getDurationAtIndex(int index);
    bool checkWhetherWillBeCleared(int index);
    
    MWArrayList *_gifFrames;
};

MW_FRAMEWORK_END

#endif /* defined(__TEXTURE_GIF_GIF_SPRITE__) */
