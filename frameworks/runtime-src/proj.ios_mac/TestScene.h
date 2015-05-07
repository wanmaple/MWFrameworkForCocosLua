//
//  TestScene.h
//  GameFramework
//
//  Created by Xin Wan on 5/7/15.
//
//

#ifndef __GameFramework__TestScene__
#define __GameFramework__TestScene__

#include "mwframework.h"

class TestScene : public mwframework::MWGameScene
{
public:
    static TestScene *create();
    
protected:
    TestScene();
    
    bool _init();
};

#endif /* defined(__GameFramework__TestScene__) */
