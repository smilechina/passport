//
//  SAPIEnforceBindingPlugin.h
//  SAPIDemo
//
//  Created by Vinson.D.Warm on 6/20/14.
//  Copyright (c) 2014 baidu. All rights reserved.
//

#import "SAPIPlugin.h"

@interface SAPIEnforceBindingPlugin : SAPIPlugin

@property (nonatomic, weak) UIViewController *webViewController;

// 强制绑定
- (void)action_unite_verify:(SAPIInvokeCommand *)command;

// 绑定成功
- (void)unite_verify_result:(SAPIInvokeCommand *)command;

@end
