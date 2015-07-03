//
//  SAPILeCaiPlugin.h
//  SAPIDemo
//
//  Created by jinsong on 12/22/14.
//  Copyright (c) 2014 baidu. All rights reserved.
//
//  此plugin用于处理和乐彩业务有关的逻辑

#import "SAPIPlugin.h"

@interface SAPILeCaiPlugin : SAPIPlugin

/**
 *  登录vc，一般应为SAPILoginViewController实例
 */
@property (nonatomic, weak) UIViewController *loginViewController;

/**
 *  当用户点击界面上的"原乐彩帐号登录"按钮时，会回调此方法
 */
- (void)action_lecai_login:(SAPIInvokeCommand *)command;

@end
