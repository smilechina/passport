//
//  SAPINuomiPlugin.h
//  SAPIDemo
//
//  Created by Vinson.D.Warm on 6/20/14.
//  Copyright (c) 2014 baidu. All rights reserved.
//

#import "SAPIPlugin.h"

@interface SAPINuomiPlugin : SAPIPlugin

@property (nonatomic, weak) UIViewController *webViewController;

// 点击“糯米登录” 入口
- (void)action_nuomi_login:(SAPIInvokeCommand *)command;

@end
