//
//  TestZipViewController.h
//  GameFramework
//
//  Created by Xin Wan on 5/7/15.
//
//

#ifndef __GameFramework__TestZipViewController__
#define __GameFramework__TestZipViewController__

#include "mwframework.h"

class TestZipViewController : public mwframework::MWViewController
{
public:
    static TestZipViewController *create();
    
    void viewDidLoad() override;
    void viewDidUnload() override;
    
protected:
    TestZipViewController();
};

#endif /* defined(__GameFramework__TestZipViewController__) */
