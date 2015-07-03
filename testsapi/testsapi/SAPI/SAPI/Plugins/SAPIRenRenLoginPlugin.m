//
//  SAPIRenRenLoginPlugin.m
//  SAPIDemo
//
//  Created by Vinson.D.Warm on 12/2/13.
//  Copyright (c) 2013 baidu. All rights reserved.
//

#import "SAPIRenRenLoginPlugin.h"
#import "SAPIMainManager.h"
#import "SAPIImageDef.h"
#import "SAPIHudHelper.H"

@implementation SAPIRenRenLoginPlugin

@synthesize loginViewController = _loginViewController;

- (void)action_social_renren_webview:(SAPIInvokeCommand *)command {
    NSURL *url = [NSURL URLWithString:[[SAPIMainManager sharedManager] renrenLoginUrl]];
    // delete cookie
    NSHTTPCookieStorage *cookieStorage = [NSHTTPCookieStorage sharedHTTPCookieStorage];
    NSArray *cookies = [cookieStorage cookiesForURL:url];
    for (NSHTTPCookie *cookie in cookies) [cookieStorage deleteCookie:cookie];
    // pop up view controller
    SAPIRenRenLoginViewController *renrenLoginViewController = [[SAPIRenRenLoginViewController alloc] initWithURL:url];
    [self.loginViewController.navigationController pushViewController:renrenLoginViewController animated:YES];
    [self toCallBackSuccessWithCommand:command];
}

@end

@interface SAPIRenRenLoginViewController () <SAPIMainWebViewDelegate>

@property (nonatomic, strong) UINavigationBar *navBar;
@property (nonatomic, strong) UIImageView *notFoundImgView;
@property (nonatomic, strong) SAPIMainWebView *mainWebView;

@end

@implementation SAPIRenRenLoginViewController

@synthesize navBar = _navBar;
@synthesize notFoundImgView = _notFoundImgView;
@synthesize url = _url;

- (void)dealloc {
    self.mainWebView.mainWebViewDelegate = nil;
    self.mainWebView.webViewDelegate = nil;
    self.mainWebView.delegate = nil;
    self.mainWebView = nil;
}

- (id)initWithURL:(NSURL *)url {
    self = [super init];
    if (self) {
        self.url = url;
    }
    return self;
}

- (void)viewDidLoad {
    [super viewDidLoad];
    [self.view addSubview:self.mainWebView];
    [self.view insertSubview:self.notFoundImgView belowSubview:self.mainWebView];
    [self createNavBar];
    [self.mainWebView load:self.url];
}

- (void)createNavBar {
    self.navBar = [[UINavigationBar alloc] initWithFrame:CGRectMake(0, 0, 320, 44)];
    UIImageView* imagView = [[UIImageView alloc]initWithImage:PNGImage(NAV_IMAGE_OF_BG)];
    [self.navBar addSubview:imagView];
	UINavigationItem *NavTitle = [[UINavigationItem alloc] initWithTitle:@"人人网登录"];
	[self.navBar pushNavigationItem:NavTitle animated:YES];
	[self.view addSubview:self.navBar];
    
    UIButton *backBtn = [UIButton buttonWithType:UIButtonTypeCustom];
    [backBtn setFrame:CGRectMake(10, 10, 50.0, 29.0)];
    [backBtn setBackgroundColor:[UIColor clearColor]];
	[backBtn setBackgroundImage:[PNGImage(NAV_IMAGE_OF_BTNBACKNORMAL) stretchableImageWithLeftCapWidth:0 topCapHeight:0] forState:UIControlStateNormal];
    [backBtn setBackgroundImage:[PNGImage(NAV_IMAGE_OF_BTNBACKPRESSED) stretchableImageWithLeftCapWidth:0 topCapHeight:0] forState:UIControlStateHighlighted];
	[backBtn addTarget:self action:@selector(goBack) forControlEvents:UIControlEventTouchUpInside];
    backBtn.titleLabel.font = FontWithSize(13);
    [backBtn setTitleColor:[UIColor whiteColor] forState:UIControlStateNormal];
    [backBtn setTitle:@"返回" forState:UIControlStateNormal];
    [backBtn setTitleEdgeInsets:UIEdgeInsetsMake(0, 5, 0, 0)];
	UIBarButtonItem *backBarBtn = [[UIBarButtonItem alloc] initWithCustomView:backBtn];
	self.navBar.topItem.leftBarButtonItem = backBarBtn;
}

- (void)goBack {
    [self.navigationController popViewControllerAnimated:YES];
}

- (void)showNotFoundView {
    self.notFoundImgView.hidden = NO;
    self.mainWebView.hidden = YES;
}

- (void)hideNotFoundView {
    self.notFoundImgView.hidden = YES;
    self.mainWebView.hidden = NO;
}

//404页面
- (UIImageView *)notFoundImgView {
    if (!_notFoundImgView) {
        UIImage *notFoundImg = PNGImage(PAGE_NOT_FOUND);
        CGFloat x = (self.view.frame.size.width - notFoundImg.size.width) / 2;
        CGFloat y = (self.view.frame.size.height - notFoundImg.size.height) / 2;
        CGRect frame = CGRectMake(x, y, notFoundImg.size.width, notFoundImg.size.height);
        _notFoundImgView = [[UIImageView alloc] initWithFrame:frame];
        _notFoundImgView.image = notFoundImg;
        _notFoundImgView.hidden = YES;
    }
    return _notFoundImgView;
}

#pragma mark - SAPIMainWebViewDelegate
- (void)sapiWebViewDidStartLoadFromNetwork:(SAPIWebView *)webView {
    [self hideNotFoundView];
    [[SAPIHudHelper getInstance] hideHud];
    [[SAPIHudHelper getInstance] showHudOnView:self.mainWebView caption:nil image:nil acitivity:YES autoHideTime:0.0];
}

- (void)sapiWebViewDidStartLoadFromCache:(SAPIWebView *)webView {
    [[SAPIHudHelper getInstance] hideHud];
}

- (void)sapiWebViewDidFinishLoadFromNetwork:(SAPIWebView *)webView {
    [[SAPIHudHelper getInstance] hideHud];
}

- (void)sapiWebViewDidFinishLoadFromCache:(SAPIWebView *)webView {
}

- (void)sapiWebView:(SAPIWebView *)webView didFailLoadFromNetWorkWithError:(NSError *)error {
    [self showNotFoundView];
    [[SAPIHudHelper getInstance] hideHud];
}

- (void)sapiWebView:(SAPIWebView *)webView didFailLoadFromCacheWithError:(NSError *)error {
    [self showNotFoundView];
}

- (SAPIMainWebView *)mainWebView {
    if (!_mainWebView) {
        _mainWebView = [[SAPIMainWebView alloc] initWithFrame:CGRectMake(0, 44, self.view.bounds.size.width, self.view.bounds.size.height - 44)];
        _mainWebView.mainWebViewDelegate = self;
    }
    return _mainWebView;
}

@end