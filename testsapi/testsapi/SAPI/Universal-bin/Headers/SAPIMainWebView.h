//
//  SAPIMainWebView.h
//  SAPILib
//
//  Created by Vinson.D.Warm on 12/27/13.
//  Copyright (c) 2013 baidu. All rights reserved.
//

#import "SAPIWebView.h"

@protocol SAPIMainWebViewDelegate <NSObject>

@optional
- (BOOL)sapiWebView:(SAPIWebView *)webView mainViewShouldStartLoadWithRequest:(NSURLRequest *)request navigationType:(UIWebViewNavigationType)navigationType;
- (void)sapiWebViewDidStartLoadFromNetwork:(SAPIWebView *)webView;
- (void)sapiWebViewDidStartLoadFromCache:(SAPIWebView *)webView;
- (void)sapiWebViewDidFinishLoadFromNetwork:(SAPIWebView *)webView;
- (void)sapiWebViewDidFinishLoadFromCache:(SAPIWebView *)webView;
- (void)sapiWebView:(SAPIWebView *)webView didFailLoadFromNetWorkWithError:(NSError *)error;
- (void)sapiWebView:(SAPIWebView *)webView didFailLoadFromCacheWithError:(NSError *)error;

@end

@interface SAPIMainWebView : SAPIWebView

@property (nonatomic, assign) BOOL viewLoaded;

@property (nonatomic, weak) id<SAPIMainWebViewDelegate> mainWebViewDelegate;

/**
 *  第三方登录是否成功
 */
@property (nonatomic, assign, getter = isThirdLoginSucceeded) BOOL thirdLoginSucceeded;

// 保存 页面包含导航栏的url列表
- (void)saveNavWhiteInfo:(NSDictionary *)whiteList;

// 检查 是否在“页面包含导航栏的url列表”里
- (BOOL)checkInWhiteList:(NSURL *)url;

// 根据 URL 获取 title
- (NSString *)titleForWhiteListURL:(NSURL *)url;

// 取消所有网络请求
- (void)cancelAllRequest;

@end
