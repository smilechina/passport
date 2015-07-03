//
//  SAPINuomiPlugin.m
//  SAPIDemo
//
//  Created by Vinson.D.Warm on 6/20/14.
//  Copyright (c) 2014 baidu. All rights reserved.
//

#import "SAPINuomiPlugin.h"
#import "SAPIHudHelper.h"

@implementation SAPINuomiPlugin

// 点击 “糯米登录” 触发
- (void)action_nuomi_login:(SAPIInvokeCommand *)command {
    NSString *type = [command.paramsInfo objectForKey:@"type"];
    NSLog(@"type: %@", type);
    [[SAPIHudHelper getInstance] showHudOnView:[UIApplication sharedApplication].keyWindow caption:@"糯米登录" image:nil acitivity:NO autoHideTime:1.0f];
}

@end
