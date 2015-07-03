//
//  SAPISinaWeiboLoginPlugin.h
//  SAPIDemo
//
//  Created by Vinson.D.Warm on 12/2/13.
//  Copyright (c) 2013 baidu. All rights reserved.
//

#import "SAPILib.h"
#import "SAPILoginViewController.h"

@interface SAPISinaWeiboLoginPlugin : SAPIPlugin

@property (nonatomic, weak) UIViewController *loginViewController;

// 点击 快捷登录 “新浪微博”按钮
- (void)action_social_sina_weibo_webview:(SAPIInvokeCommand *)command;

@end

@interface SAPISinaWeiboLoginViewController : UIViewController

@property (nonatomic, strong) NSURL *url;

- (id)initWithURL:(NSURL *)url;

@end
