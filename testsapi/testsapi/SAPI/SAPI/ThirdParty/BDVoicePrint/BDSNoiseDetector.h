//
//  BDSNoiseDetector.h
//  BDSSpeakerRecognition
//
//  Created by 唐海员 on 14-7-15.
//  Copyright (c) 2014年 百度. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "BDSNoiseDetectorDelegate.h"

@interface BDSNoiseDetector : NSObject
/**
 * @brief 初始化噪音检测器
 *
 * @param dlgt 检测器的委托对象
 *
 * @return 检测器实例
 */
- (instancetype)initWithDelegate:(id<BDSNoiseDetectorDelegate>)dlgt;

/**
 * @brief 执行噪音检测
 *
 */
- (void)detect;
@end
