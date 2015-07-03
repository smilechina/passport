//
//  SAPISinaSSOLoginPlugin.h
//  SAPIDemo
//
//  Created by Vinson.D.Warm on 13-9-23.
//  Copyright (c) 2013年 baidu. All rights reserved.
//

#import "SAPILib.h"
#import "SAPILoginViewController.h"
#import "SinaWeibo.h"

#define SSO_FINISH_AUTH_URL     @"/phoenix/account/ssologin"
#define SSO_FINISH_BIND_URL     @"/phoenix/account/finishbind"

//第3方登录标记名
#define OAUTH_NAME                                  @"oauth"
//新浪微博SSO登录分配的appkey
#define WEIBO_SSO_APP_KEY                           @"2512457640"
#define WEIBO_SSO_APP_SECRET                        @"9b927de7dcac0ba1432b7051d018cb59"
//应用回调页，新浪微博SSO进行Oauth2.0登录认证时使用
#define WEIBO_SSO_REDIRECT_URL                      @"http://www.baidu.com"
//格式：sinaweibosso.WEIBO_SSO_APP_KEY.TPL
#define WEIBO_SSO_CALLBACK_URL_SCHEMA               @"sinaweibosso.2512457640.lo"
#define SSO_LOGIN_TYPE_WEIBO                        @"2"
//绑定类型：implicit－暗绑，explicit－明绑，optional－选择性绑定
#define _BIND_TYPE                                  @"&act=optional"

@interface SAPISinaSSOLoginPlugin : SAPIPlugin

@property (nonatomic, strong) SinaWeibo *sinaWeibo;

@property (nonatomic, weak) UIViewController *loginViewController;

// 使用新浪微博sso登录
- (void)action_social_sina_sso:(SAPIInvokeCommand *)command;

+ (SAPISinaSSOLoginPlugin *)sharedPlugin;

@end
