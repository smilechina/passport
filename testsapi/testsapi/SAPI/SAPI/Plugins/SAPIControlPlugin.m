//
//  SAPIControlPlugin.m
//  SAPIDemo
//
//  Created by Vinson.D.Warm on 12/4/13.
//  Copyright (c) 2013 baidu. All rights reserved.
//

#import "SAPIControlPlugin.h"
#import "SAPIMainManager.h"
//#import "SAPISMSLoginViewController.h"

@implementation SAPIControlPlugin

@synthesize webViewController = _webViewController;

- (void)finish:(SAPIInvokeCommand *)command {
    // 默认为pop，与SAPILoginViewController登录vc被push进来相对应。
    // 产品线如果想采用pesent的方法呈现SAPILoginViewController，则此处应相应的采用dismiss方法
    [self.webViewController.navigationController popViewControllerAnimated:YES];
    [self toCallBackSuccessWithCommand:command];
}

- (void)action_bind_widget_phone_number_exist:(SAPIInvokeCommand *)command {
    // 可考虑直接跳转短信登录界面
    NSString *mobile = [NSString stringWithFormat:@"%@", [command.paramsInfo objectForKey:@"mobile"]];
    [SAPIMainManager sharedManager].inputPlaceholderPhoneNumber = mobile;
//    SAPISMSLoginViewController *smsLoginVC = [[SAPISMSLoginViewController alloc] init];
//    [self.webViewController.navigationController pushViewController:smsLoginVC animated:YES];
    
}

@end
