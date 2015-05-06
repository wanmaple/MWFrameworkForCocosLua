/******************************
 Description: SVG sprite.
 Author: M.Wan
 Date: 5/5/2015
 ******************************/

#ifndef __TEXTURE_SVG_SVG_SPRITE__
#define __TEXTURE_SVG_SVG_SPRITE__

#include "../../base/mwbase.h"
#include "cocos2d.h"
#include <string>

MW_FRAMEWORK_BEGIN

/**
 * SVG Sprite
 */
class MW_DLL MWSvgSprite : public cocos2d::Sprite
{
public:
    /**
     * Create svg sprite by an svg vector image path.
     *
     * @param svgPath SVG file path.
     * @param dpi Preferred dpi.
     */
    static MWSvgSprite *createWithFile(const std::string &svgPath, float dpi = 72.0f);
    /**
     * Create svg sprite with binary data.
     *
     * @param imgData SVG binary data.
     * @param dpi Preferred dpi.
     */
    static MWSvgSprite *createWithRawData(MWBinaryData *imgData, float dpi = 72.0f);
    
    /**
     * SVG Sprite destructor.
     */
    virtual ~MWSvgSprite();
    
    void setVectorScale(float scale);
    MW_SYNTHESIZE_READONLY(float, _vectorScale, VectorScale);
    
protected:
    bool initWithFile(const std::string &svgPath, float dpi);
    bool initWithRawData(MWBinaryData *imgData, float dpi);
    
    cocos2d::Texture2D *getScaledTexture(float scale);
    
    MWSvgSprite();
};

MW_FRAMEWORK_END

#endif
