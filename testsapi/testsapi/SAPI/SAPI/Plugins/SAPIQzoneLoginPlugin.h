//
//  SAPIQzoneLoginPlugin.h
//  SAPIDemo
//
//  Created by Vinson.D.Warm on 12/2/13.
//  Copyright (c) 2013 baidu. All rights reserved.
//

#import "SAPILib.h"
#import "SAPILoginViewController.h"

@interface SAPIQzoneLoginPlugin : SAPIPlugin

@property (nonatomic, weak) UIViewController *loginViewController;

// 点击 快捷登录 “QQ” 按钮
- (void)action_social_qzone_webview:(SAPIInvokeCommand *)command;

@end


@interface SAPIQzoneLoginViewController : UIViewController

@property (nonatomic, strong) NSURL *url;

- (id)initWithURL:(NSURL *)url;

@end