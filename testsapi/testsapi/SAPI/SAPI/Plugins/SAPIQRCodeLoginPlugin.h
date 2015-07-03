//
//  SAPIQRCodeLoginPlugin.h
//  SAPIDemo
//
//  Created by Vinson.D.Warm on 12/2/13.
//  Copyright (c) 2013 baidu. All rights reserved.
//

#import "SAPILib.h"
#import "SAPILoginViewController.h"

@interface SAPIQRCodeLoginPlugin : SAPIPlugin

@property (nonatomic, weak) UIViewController *loginViewController;

// 点击 快捷登录 “二维码登录”按钮
- (void)loginWithQRCode:(SAPIInvokeCommand *)command;

@end
