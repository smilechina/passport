//
//  SAPIWeiXinSSOLoginPlugin.m
//  SAPIDemo
//
//  Created by jinsong on 11/12/14.
//  Copyright (c) 2014 baidu. All rights reserved.
//

#import "SAPIWeiXinSSOLoginPlugin.h"
#import "WXApi.h"
#import "SAPILib.h"
#import "SAPIHudHelper.h"
#import "SAPIWeiXinSSOViewController.h"

#warning 请替换为产品线从passport申请的微信AppId，申请事宜请在Hi上联系吕太龙
#define SAPI_WeiXin_SSO_AppId     @"wx7c58cdd3c17bc3a6"

// 第三方帐号与百度帐号的绑定方式：implicit－暗绑、explicit－明绑、optional－选择性绑定
#define kBindType @"implicit"

// 微信登录时的默认授权域，不需要修改
#define kDefaultWeiXinLoginScope @"snsapi_userinfo"

@interface SAPIWeiXinSSOLoginPlugin () <WXApiDelegate>

@end

@implementation SAPIWeiXinSSOLoginPlugin

#pragma mark - LifeCycle
+ (SAPIWeiXinSSOLoginPlugin *)sharedPlugin {
    static SAPIWeiXinSSOLoginPlugin *_plugin = nil;
    static dispatch_once_t onceToken;
    dispatch_once(&onceToken, ^{
        _plugin = [[SAPIWeiXinSSOLoginPlugin alloc] init];
    });
    return _plugin;
}

- (id)init {
    if (self = [super init]) {
        
        _wxScope = kDefaultWeiXinLoginScope;
        _wxAppId = SAPI_WeiXin_SSO_AppId;
        _bindType = kBindType;
        
        [WXApi registerApp:_wxAppId withDescription:[[NSBundle mainBundle] bundleIdentifier]];
    }
    return self;
}

#pragma mark - Public Method
- (void)SAPIHandleWeiXinLogin:(NSDictionary *)loginInfo {
    NSInteger errCode = [loginInfo[@"errCode"] integerValue];
    
    if (errCode == 0) {
        
        SendAuthReq *authReq = [[SendAuthReq alloc] init];
        authReq.scope = self.wxScope;
        authReq.state = loginInfo[@"state"];
        [WXApi sendReq:authReq];
        
    } else {
        [[SAPIHudHelper getInstance] showHudOnWindow:loginInfo[@"errMsg"] image:nil acitivity:NO autoHideTime:2.f];
    }
}

- (BOOL)handleOpenURL:(NSURL *)url {
    return [WXApi handleOpenURL:url delegate:self];
}

+ (BOOL)isWeiXinInstalled {
    NSURL *url1 = [NSURL URLWithString:@"weixin://"];
    NSURL *url2 = [NSURL URLWithString:@"wechat://"];
    NSURL *url3 = [NSURL URLWithString:@"fb290293790992170://"];
    
    BOOL isWXInstalled =
    [[UIApplication sharedApplication] canOpenURL:url1]
    || [[UIApplication sharedApplication] canOpenURL:url2]
    || [[UIApplication sharedApplication] canOpenURL:url3];
    
    return isWXInstalled;
}

#pragma mark - WXDelegate
- (void)onResp:(BaseResp *)resp {
    if ([resp isKindOfClass:[SendAuthResp class]]) {
        [self handleWeiXinAuthResq:(SendAuthResp *)resp];
    }
}

#pragma mark - Private Method
/**
 *  根据微信的返回结果，继续登录流程
 *
 *  @param authResp resp具体的回应内容
 */
- (void)handleWeiXinAuthResq:(SendAuthResp *)authResp {
    if (authResp.errCode == 0) {
        
        SAPIWeiXinSSOViewController *wxLoginVC = [[SAPIWeiXinSSOViewController alloc] init];
        wxLoginVC.code = authResp.code;
        
        // 默认优先采用push
        if (self.containerVC.navigationController) {
            wxLoginVC.prensentVCMode = NO;
            [self.containerVC.navigationController pushViewController:wxLoginVC animated:NO];
        } else {
            
            /**
             *  产品线如果采用- (void)presentViewController:(UIViewController *)viewControllerToPresent animated:(BOOL)flag completion:(void (^)(void))completion方法来展现SAPIWeiXinSSOViewController，
             *  SAPI会在登录成功以后，在SAPIWeiXinSSOViewController的- (void)webViewDidFinishLoad的方法中调用相应的VC dismiss方法，以便使在登录成功时整个页面跳转逻辑完备，而不会导致登录成功后继续停留在SAPIWeiXinSSOViewController的页面
             *
             */
            wxLoginVC.prensentVCMode = YES;
            UINavigationController *nav = [[UINavigationController alloc] initWithRootViewController:wxLoginVC];
            [self.containerVC presentViewController:nav animated:NO completion:nil];
        }
        
    } else {
#ifdef DEBUG
        NSLog(@"<(Line: %d) %s> errCode: %d, errStr: %@", __LINE__, __func__, authResp.errCode, authResp.errStr);
#endif
        [[SAPIHudHelper getInstance] showHudOnWindow:@"你已取消微信登录" image:nil acitivity:NO autoHideTime:2.f];
    }
}

@end
