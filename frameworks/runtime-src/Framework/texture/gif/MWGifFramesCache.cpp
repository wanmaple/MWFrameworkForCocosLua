#include "MWGifFramesCache.h"

#include "cocos2d.h"
#include "MWGifFrame.h"
#include "MWGifSprite.h"

using namespace cocos2d;
using namespace std;

MW_FRAMEWORK_BEGIN

MWGifFramesCache::MWGifFramesCache()
: _cachedGifs(new MWDictionary())
{
    
}

void MWGifFramesCache::addGifFramesCache(const std::string &gifPath)
{
    auto pGif = MWGifSprite::createWithFile(gifPath);
    if (pGif) {
    this->addGifFramesCache(pGif, FileUtils::getInstance()->fullPathForFilename(gifPath));
    }
}

void MWGifFramesCache::addGifFramesCache(mwframework::MWBinaryData *data, const std::string &key)
{
    auto pGif = MWGifSprite::createWithRawData(data);
    if (pGif) {
    this->addGifFramesCache(pGif, key);
    }
}

void MWGifFramesCache::addGifFramesCache(mwframework::MWGifSprite *gifSprite, const std::string &key)
{
    if (!gifSprite || key.size() <= 0) {
        return;
    }
    auto pFrames = gifSprite->getFrames();
    if (pFrames && pFrames->count() > 0) {
        this->addGifFramesCache(pFrames, key);
    }
}

void MWGifFramesCache::addGifFramesCache(mwframework::MWArrayList *frames, const std::string &key)
{
    if (!frames || frames->count() <= 0 || key.size() <= 0) {
        return;
    }
    _cachedGifs->setObjectForKey(key, frames);
}

void MWGifFramesCache::removeGifFramesCache(const std::string &key)
{
    if (key.size() > 0) {
        _cachedGifs->removeObjectForKey(key);
    }
}

void MWGifFramesCache::removeAll()
{
    _cachedGifs->clear();
}

MWGifSprite *MWGifFramesCache::getGifSprite(const std::string &key)
{
    if (_cachedGifs->hasKey(key)) {
        return MWGifSprite::createWithFrames(static_cast<MWArrayList *>(_cachedGifs->objectForKey(key)));
    }
    return nullptr;
}

MW_FRAMEWORK_END