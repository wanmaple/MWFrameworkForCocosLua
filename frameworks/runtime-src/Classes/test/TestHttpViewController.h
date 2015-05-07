//
//  TestHttpViewController.h
//  GameFramework
//
//  Created by Xin Wan on 5/7/15.
//
//

#ifndef __GameFramework__TestHttpViewController__
#define __GameFramework__TestHttpViewController__

#include "mwframework.h"

class TestHttpViewController : public mwframework::MWViewController
{
public:
    static TestHttpViewController *create();
    
    void viewDidLoad() override;
    void viewDidUnload() override;
    
protected:
    TestHttpViewController();
};

#endif /* defined(__GameFramework__TestHttpViewController__) */
