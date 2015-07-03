//
//  SAPIForgetPwdPlugin.m
//  SAPIDemo
//
//  Created by Vinson.D.Warm on 4/1/14.
//  Copyright (c) 2014 baidu. All rights reserved.
//

#import "SAPIForgetPwdPlugin.h"
#import "SAPIMainManager.h"
#import "SAPIImageDef.h"
#import "SAPIHudHelper.H"
#import "SAPIControlPlugin.h"
#import "SAPINavPlugin.h"

@implementation SAPIForgetPwdPlugin

- (void)action_forget_pwd:(SAPIInvokeCommand *)command {
    NSURL *url = [NSURL URLWithString:[[SAPIMainManager sharedManager] forgetPwdUrl]];
    SAPIForgetPwdViewController *forgetPwdVC = [[SAPIForgetPwdViewController alloc] initWithURL:url];
    [self.webViewController.navigationController pushViewController:forgetPwdVC animated:YES];
    NSDictionary *resultInfo = @{@"result" : [NSNumber numberWithInt:1]};
    [self toCallBackSuccess:resultInfo callBackId:command.callBackId];
}

@end


@interface SAPIForgetPwdViewController () <SAPIMainWebViewDelegate>

@property (nonatomic, strong) UINavigationBar *navBar;
@property (nonatomic, strong) UIImageView *notFoundImgView;
@property (nonatomic, strong) SAPIMainWebView *mainWebView;

@end

@implementation SAPIForgetPwdViewController

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
    [self initPlugins];
    [self.mainWebView load:self.url];
}

- (void)initPlugins {
    // 控制插件
    SAPIControlPlugin *controlPlugin = [[SAPIControlPlugin alloc] init];
    controlPlugin.webViewController = self;
    [self.mainWebView addPlugin:controlPlugin];
}

- (void)createNavBar {
    self.navBar = [[UINavigationBar alloc] initWithFrame:CGRectMake(0, 0, 320, 44)];
    UIImageView* imagView = [[UIImageView alloc]initWithImage:PNGImage(NAV_IMAGE_OF_BG)];
    [self.navBar addSubview:imagView];
	UINavigationItem *NavTitle = [[UINavigationItem alloc] initWithTitle:@"忘记密码"];
	[self.navBar pushNavigationItem:NavTitle animated:YES];
	[self.view addSubview:self.navBar];
    
    UIButton *backBtn = [UIButton buttonWithType:UIButtonTypeCustom];
    [backBtn setFrame:CGRectMake(10, 10, 50.0, 29.0)];
    [backBtn setBackgroundColor:[UIColor clearColor]];
	[backBtn setBackgroundImage:[PNGImage(NAV_IMAGE_OF_BTNBACKNORMAL) stretchableImageWithLeftCapWidth:0 topCapHeight:0] forState:UIControlStateNormal];
    [backBtn setBackgroundImage:[PNGImage(NAV_IMAGE_OF_BTNBACKPRESSED) stretchableImageWithLeftCapWidth:0 topCapHeight:0] forState:UIControlStateHighlighted];
	[backBtn addTarget:self action:@selector(goBack:) forControlEvents:UIControlEventTouchUpInside];
    backBtn.titleLabel.font = FontWithSize(13);
    [backBtn setTitleColor:[UIColor whiteColor] forState:UIControlStateNormal];
    [backBtn setTitle:@"返回" forState:UIControlStateNormal];
    [backBtn setTitleEdgeInsets:UIEdgeInsetsMake(0, 5, 0, 0)];
	UIBarButtonItem *backBarBtn = [[UIBarButtonItem alloc] initWithCustomView:backBtn];
	self.navBar.topItem.leftBarButtonItem = backBarBtn;
}

- (void)goBack:(id)sender {
    if (!self.mainWebView.viewLoaded) {
        [self.navigationController popViewControllerAnimated:YES];
        return;
    }
    if (![self.mainWebView historyBack]) {
        [self.navigationController popViewControllerAnimated:YES];
    }
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