//
//  SAPIWeiXinSSOLoginPlugin.h
//  SAPIDemo
//
//  Created by jinsong on 11/12/14.
//  Copyright (c) 2014 baidu. All rights reserved.
//

#import "SAPIPlugin.h"

@interface SAPIWeiXinSSOLoginPlugin : SAPIPlugin

/**
 *  微信登录时的默认授权域，默认为"snsapi_userinfo"，产品线不用修改
 */
@property (nonatomic, copy) NSString *wxScope;

/**
 *  产品线从passport处获取的微信AppId
 */
@property (nonatomic, copy) NSString *wxAppId;

/**
 *  第三方帐号与百度帐号的绑定方式 默认为"implicit"－暗绑，产品线可根据策略选择明绑、选择性绑定策略
 */
@property (nonatomic, copy) NSString *bindType;

/**
 *  包含微信登录plugin的视图控制器，一般应为SAPILoginViewController
 */
@property (nonatomic, weak) UIViewController *containerVC;



/**
 *  主要用来处理和微信有关的业务，如登录、分享、支付等。
 *  默认只处理了和SAPI有关的登录业务，其他微信业务的逻辑须由产品线自己合入微信的回调方法- (void)onResp:(BaseResp *)resp
 *
 *  @return SAPIWeiXinSSOLoginPlugin的单例
 */
+ (SAPIWeiXinSSOLoginPlugin *)sharedPlugin;



/**
 *  SAPI处理相关参数成功并准备拉起微信前，或者参数处理错误时的回调
 *
 *  @param loginInfo 返回一个键值对，包含以下三个字段：
 *      错误码（errCode）    错误描述（errMsg）                    状态码（state，只在errCode为0时返回本字段）
 *              0        所有信息正常，可发起微信登录            字符串，传给微信登录时的state字段即可
 *              1              服务器繁忙
 *              2              网络错误
 *              3     参数错误（wxScope、wxAppId、bindType错误）
 */
- (void)SAPIHandleWeiXinLogin:(NSDictionary *)loginInfo;



/**
 *  用微信处理可能的跳转结果，请在UIApplicationDelegate的
 *  - (BOOL)application:(UIApplication *)application openURL:(NSURL *)url sourceApplication:(NSString *)sourceApplication annotation:(id)annotation方法中，
 *  或者
 *  - (BOOL)application:(UIApplication *)application handleOpenURL:(NSURL *)url方法中
 *  调用本方法
 *
 *  @param url 待处理的url
 *
 *  @return 返回YES表示微信的SDK能够响应传入的URL；返回NO则相反
 */
- (BOOL)handleOpenURL:(NSURL *)url;



/**
 *  用于判断设备上是否已经安装了微信，微信SDK提供的方法有时候不准确
 *  由于微信只提供了SSO登录，如果设备上没有安装微信，不推荐在登录页面中显示微信登录
 *
 *  @return 返回YES表示设备已经安装微信；返回NO则相反
 */
+ (BOOL)isWeiXinInstalled;

@end
