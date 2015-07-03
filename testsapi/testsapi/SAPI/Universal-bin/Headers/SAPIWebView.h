//
//  SAPIWebView.h
//  SAPIBridge
//
//  Created by Vinson.D.Warm on 9/3/13.
//  Copyright (c) 2013 SAPI. All rights reserved.
//

#import <UIKit/UIKit.h>
#import "SAPIPlugin.h"

@class SAPIWebView;
@class SAPILoginModel;

@protocol SAPIWebViewDelegate <NSObject>

@optional
- (BOOL)sapiWebView:(SAPIWebView *)webView shouldStartLoadWithRequest:(NSURLRequest *)request navigationType:(UIWebViewNavigationType)navigationType;
- (void)sapiWebViewDidStartLoad:(SAPIWebView *)webView;
- (void)sapiWebViewDidFinishLoad:(SAPIWebView *)webView;
- (void)sapiWebView:(SAPIWebView *)webView didFailLoadWithError:(NSError *)error;

@end

@interface SAPIWebView : UIWebView

@property (nonatomic, strong) SAPIPlugin *plugin;

@property (nonatomic, strong) NSMutableArray *plugins;

@property (nonatomic, weak) id<SAPIWebViewDelegate> webViewDelegate;

- (id)initWithPlugin:(SAPIPlugin *)plugin;

- (void)load:(NSURL *)url;

- (void)load:(NSURL *)url cookies:(NSArray *)cookies;

/**
 *  根据传入参数加载指定URL
 *
 *  v6.8.3新增
 *
 *  @param url             需加载的url
 *  @param cookies         根据场景需要传入的cookies
 *  @param persistentBduss 如果传入的cookies里包含有bduss时，该bduss是否作为持久性cookie写入NSHTTPCookieStorage
 *                         如果传入NO，则直接将传入的该bduss cookie写入NSHTTPCookieStorage
 *                         如果传入YES，则根据传入的该bduss cookie创建一个新的非SessionOnly的bduss cookie写入
 *                         NSHTTPCookieStorage
 */
- (void)load:(NSURL *)url cookies:(NSArray *)cookies persistentBduss:(BOOL)persistent;

- (void)addPlugin:(SAPIPlugin *)plugin;

- (BOOL)historyBack;

- (NSURL *)currentURL;

- (void)addBlackListModule:(NSURL *)url;

- (void)clean;

/**
 *  在注册、登录界面采用native导航栏时，如果需要回退到上一个webview页面时可调用此方法
 *
 *  v6.7.10新增
 *
 *  调用时有以下两种情况：
 *  1.如果webview可以回退，则会回退到上一个页面；
 *  2.如果不能回退，则会调用注册到webview的SAPIControlPlugin中的finish:方法来关闭整个视图控制器（或执行其他操作）
 */
- (void)sapiWebViewGoBackIfPossible;

@end

@interface SAPIWebView (SAPIWebViewLoadAddition)

/**
 *  在从微信App获取到code后调用，通过webview传递该参数去换取access_token后获取微信帐号信息，及与之对应的百度帐号信息
 *
 *  @param code 微信App返回字段，用于换取access_token
 */
- (void)loadWeiXinBindURLWithCode:(NSString *)code;

- (void)loadLoginVerifyWithURLString:(NSString *)urlString;

/**
 *  对半帐号进行正常化
 *
 *  @param bduss    需要正常化帐号的bduss
 *  @param callback 正常化以后的回调。正常化成功时会回传一个SAPILoginModel实例；失败时会回传一个NSError实例
 */
- (void)loadAccountNormalizationURLWithBduss:(NSString *)bduss callback:(void(^)(SAPILoginModel *model, NSError *error))callback;

/**
 *  对半帐号进行正常化
 *
 *  @param bduss      需要正常化帐号的bduss
 *
 *  @param persistent 是否将传入的bduss作为持久性cookie写入NSHTTPCookieStorage
 *                    如果传入NO，则根据传入的bduss创建一个SessionOnly的bduss cookie写入NSHTTPCookieStorage；
 *                    如果传入YES，则根据传入的bduss创建一个非SessionOnly的bduss cookie写入NSHTTPCookieStorage
 *
 *  @param callback   正常化以后的回调。正常化成功时会回传一个SAPILoginModel实例；失败时会回传一个NSError实例
 */
- (void)loadAccountNormalizationURLWithBduss:(NSString *)bduss persistentBduss:(BOOL)persistent callback:(void(^)(SAPILoginModel *model, NSError *error))callback;

@end
