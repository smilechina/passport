//
//  SAPIDeviceTokenLoginPlugin.h
//  SAPIDemo
//
//  Created by Vinson.D.Warm on 12/2/13.
//  Copyright (c) 2013 baidu. All rights reserved.
//

#import "SAPILib.h"
#import "SAPILoginViewController.h"

@interface SAPIDeviceTokenLoginPlugin : SAPIPlugin

@property (nonatomic, weak) SAPILoginViewController *loginViewController;

// 点击 快捷登录 “设备号登录” 按钮
- (void)loginWithDeviceId:(SAPIInvokeCommand *)command;

@end
