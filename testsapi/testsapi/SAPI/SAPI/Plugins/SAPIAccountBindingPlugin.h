//
//  SAPIEnforceBindingPlugin.h
//  SAPIDemo
//
//  Created by Vinson.D.Warm on 6/20/14.
//  Copyright (c) 2014 baidu. All rights reserved.
//

#import "SAPIPlugin.h"

@interface SAPIAccountBindingPlugin : SAPIPlugin

@property (nonatomic, weak) UIViewController *webViewController;

// 绑定成功
- (void)unite_verify_result:(SAPIInvokeCommand *)command;

@end
