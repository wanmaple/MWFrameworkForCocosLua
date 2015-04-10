#include "cocos2d.h"

#if CC_TARGET_PLATFORM == CC_PLATFORM_IOS

#include "MWSystemHelperStrategyIOS.h"

#import <Foundation/Foundation.h>
#import <UIKit/UIKit.h>

#import <sys/sysctl.h>
#import <mach/mach.h>

MW_FRAMEWORK_BEGIN

void MWSystemHelperStrategyIos::copyToPasteBoard(const std::string &content)
{
    UIPasteboard *pPasteBoard = [UIPasteboard generalPasteboard];
    pPasteBoard.string = [NSString stringWithUTF8String:content.c_str()];
}

double MWSystemHelperStrategy::getCurrentUsedMemory()
{
    task_basic_info_data_t taskInfo;
    mach_msg_type_number_t infoCount = TASK_BASIC_INFO_COUNT;
    kern_return_t kernReturn = task_info(mach_task_self(), TASK_BASIC_INFO, (task_info_t)&taskInfo, &infoCount);
    
    if (kernReturn != KERN_SUCCESS) {
        return NSNotFound;
    }
    
    return taskInfo.resident_size / 1024.0f / 1024.0f;
}

MW_FRAMEWORK_END

#endif