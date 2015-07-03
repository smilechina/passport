//
//  BDSNoiseDetectorDelegate.h
//  BDSSpeakerRecognition
//
//  Created by 唐海员 on 14-7-15.
//  Copyright (c) 2014年 百度. All rights reserved.
//

#import <Foundation/Foundation.h>

@protocol BDSNoiseDetectorDelegate <NSObject>
/**
 * @brief 返回噪音检测结果
 *
 * @param result 噪音检测结果，0 silence，1 noise，-1 error
 *
 */
- (void)onComplete:(int)result;
@end
