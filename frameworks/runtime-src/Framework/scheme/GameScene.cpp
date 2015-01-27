#include "GameScene.h"
#include "cocos2d.h"
#include <new>

using namespace cocos2d;
using namespace std;

namespace mwframework {
    GameScene *GameScene::create()
    {
        auto pScene = new (nothrow) GameScene();
        if (pScene && pScene->init()) {
            pScene->autorelease();
            return pScene;
        }
        CC_SAFE_RELEASE(pScene);
        return nullptr;
    }
}