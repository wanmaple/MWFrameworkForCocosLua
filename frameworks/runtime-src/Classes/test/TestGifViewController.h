//
//  TestGifViewController.h
//  GameFramework
//
//  Created by Xin Wan on 5/7/15.
//
//

#ifndef __GameFramework__TestGifViewController__
#define __GameFramework__TestGifViewController__

#include "mwframework.h"

class TestGifViewController : public mwframework::MWViewController
{
public:
    static TestGifViewController *create();
    
    void viewDidLoad() override;
    void viewDidUnload() override;
    
protected:
    TestGifViewController();
};

#endif /* defined(__GameFramework__TestGifViewController__) */
