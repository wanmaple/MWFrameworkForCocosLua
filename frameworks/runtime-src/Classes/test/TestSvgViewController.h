//
//  TestSvgViewController.h
//  GameFramework
//
//  Created by Xin Wan on 5/7/15.
//
//

#ifndef __GameFramework__TestSvgViewController__
#define __GameFramework__TestSvgViewController__

#include "mwframework.h"

class TestSvgViewController : public mwframework::MWViewController
{
public:
    static TestSvgViewController *create();
    
    void viewDidLoad() override;
    void viewDidUnload() override;
    
protected:
    TestSvgViewController();
};

#endif /* defined(__GameFramework__TestSvgViewController__) */
