//
//  SAPITXWeiboLoginPlugin.h
//  SAPIDemo
//
//  Created by Vinson.D.Warm on 12/2/13.
//  Copyright (c) 2013 baidu. All rights reserved.
//

#import "SAPIPlugin.h"
#import "SAPILoginViewController.h"

@interface SAPITXWeiboLoginPlugin : SAPIPlugin

@property (nonatomic, weak) UIViewController *loginViewController;

// 点击 快捷登录 “腾讯微博” 按钮
- (void)action_social_tx_weibo_webview:(SAPIInvokeCommand *)command;

@end

@interface SAPITXWeiboLoginViewController : UIViewController

@property (nonatomic, strong) NSURL *url;

- (id)initWithURL:(NSURL *)url;

@end
