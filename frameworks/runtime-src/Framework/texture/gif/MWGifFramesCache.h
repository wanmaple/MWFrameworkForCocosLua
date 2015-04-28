/******************************
 Description: GIF sprite.
 Author: M.Wan
 Date: 4/14/2015
 ******************************/

#ifndef __TEXTURE_GIF_GIF_FRAMES_CACHE__
#define __TEXTURE_GIF_GIF_FRAMES_CACHE__

#include "../../base/mwbase.h"
#include "cocos2d.h"
#include <string>

MW_FRAMEWORK_BEGIN

class MWGifSprite;

/**
 * Gif cache manager.
 */
class MW_DLL MWGifFramesCache : public MWObject, public IUninheritable<MWGifFramesCache>
{
    MW_SINGLETON(MWGifFramesCache);
public:
    /**
     * Cache the gif with the path.
     *
     * @param gifPath Gif image path.
     */
    void addGifFramesCache(const std::string &gifPath);
    
    /**
     * Cache the gif frames with raw data.
     *
     * @param data Gif raw data.
     * @param key The key to save the cache.
     */
    void addGifFramesCache(MWBinaryData *data, const std::string &key);
    
    /**
     * Cache the gif frames.
     *
     * @param gifSprite Gif sprite.
     * @param key The key to save the cache.
     */
    void addGifFramesCache(MWGifSprite *gifSprite, const std::string &key);
    
    /**
     * Cache the gif frames.
     *
     * @param frames Gif frames.
     * @param key The key to save the cache.
     */
    void addGifFramesCache(MWArrayList *frames, const std::string &key);
    
    /**
     * Remove the gif cache.
     *
     * @param key The related key to remove.
     */
    void removeGifFramesCache(const std::string &key);
    
    /**
     * Remove all gif cache.
     */
    void removeAll();
    
    /**
     * Get the gif sprite from the specified key.
     *
     * @param key Cached key.
     */
    MWGifSprite *getGifSprite(const std::string &key);
    
protected:
    MWDictionary *_cachedGifs;
};

MW_FRAMEWORK_END

#endif
