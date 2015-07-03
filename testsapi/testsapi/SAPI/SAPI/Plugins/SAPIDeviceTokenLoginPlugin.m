//
//  SAPIDeviceTokenLoginPlugin.m
//  SAPIDemo
//
//  Created by Vinson.D.Warm on 12/2/13.
//  Copyright (c) 2013 baidu. All rights reserved.
//

#import "SAPIDeviceTokenLoginPlugin.h"
#import "SAPIHudHelper.h"

@implementation SAPIDeviceTokenLoginPlugin

@synthesize loginViewController = _loginViewController;

- (void)loginWithDeviceId:(SAPIInvokeCommand *)command {
    [[SAPIHudHelper getInstance] showHudOnView:[UIApplication sharedApplication].keyWindow caption:@"登录中..." image:nil acitivity:YES autoHideTime:0.0f];
    [[[SAPIMainManager sharedManager] loginService] loginWithDeviceIdOnCompletion:^(NSDictionary *info) {
        [[SAPIHudHelper getInstance] hideHud];
        SAPILoginModel *loginModel = [[SAPILoginModel alloc] initWithDictionary:info];
        [[SAPIMainManager sharedManager] loginWithLoginModel:loginModel];
        [self toCallBackSuccessWithCommand:command];
    } onError:^(NSDictionary *errorInfo) {
        [[SAPIHudHelper getInstance] hideHud];
        [self toCallBackErrorWithCommand:command];
    }];
}

@end
