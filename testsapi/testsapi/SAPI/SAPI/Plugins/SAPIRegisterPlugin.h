//
//  SAPIRegisterPlugin.h
//  SAPIDemo
//
//  Created by Vinson.D.Warm on 13-9-26.
//  Copyright (c) 2013年 baidu. All rights reserved.
//

#import "SAPIPlugin.h"
#import "SAPILib.h"

@interface SAPIRegisterPlugin : SAPIPlugin

@property (nonatomic, weak) UIViewController *webViewController;
@property (nonatomic, weak) SAPIMainWebView *mainWebView;

// 快速注册
- (void)action_fast_reg:(SAPIInvokeCommand *)command;

- (void)cancelAllRequest;

@end
