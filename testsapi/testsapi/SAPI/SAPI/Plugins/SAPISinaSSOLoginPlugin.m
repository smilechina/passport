//
//  SAPISinaSSOLoginPlugin.m
//  SAPIDemo
//
//  Created by Vinson.D.Warm on 13-9-23.
//  Copyright (c) 2013年 baidu. All rights reserved.
//

#import "SAPISinaSSOLoginPlugin.h"
#import "SinaSSOViewController.h"

@interface SAPISinaSSOLoginPlugin () <SinaWeiboDelegate>

@property (nonatomic, strong) SAPIInvokeCommand *sinaSSOCommand;

@end

@implementation SAPISinaSSOLoginPlugin

@synthesize sinaWeibo = _sinaWeibo;
@synthesize sinaSSOCommand = _sinaSSOCommand;

@synthesize loginViewController = _loginViewController;

+ (SAPISinaSSOLoginPlugin *)sharedPlugin {
    static SAPISinaSSOLoginPlugin *_sharedPlugin = nil;
    static dispatch_once_t onceToken;
    dispatch_once(&onceToken, ^{
        _sharedPlugin = [[SAPISinaSSOLoginPlugin alloc] init];
    });
    return _sharedPlugin;
}

- (id)init {
    self = [super init];
    if (self) {
        [[NSNotificationCenter defaultCenter] addObserver:self
                                                 selector:@selector(applicationWillEnterForeground:)
                                                     name:UIApplicationWillEnterForegroundNotification
                                                   object:nil];
        
        [[NSNotificationCenter defaultCenter] addObserver:self
                                                 selector:@selector(applicationDidBecomeActive:)
                                                     name:UIApplicationDidBecomeActiveNotification
                                                   object:nil];
    }
    return self;
}

- (void)action_social_sina_sso:(SAPIInvokeCommand *)command {
    self.sinaSSOCommand = command;
    [self login];
}

- (void)login {
    [self.sinaWeibo logOut];
    [self.sinaWeibo logIn];
}

- (SinaWeibo *)sinaWeibo {
    if (!_sinaWeibo) {
        _sinaWeibo = [[SinaWeibo alloc] initWithAppKey:WEIBO_SSO_APP_KEY
                                             appSecret:WEIBO_SSO_APP_SECRET
                                        appRedirectURI:WEIBO_SSO_REDIRECT_URL
                                     ssoCallbackScheme:WEIBO_SSO_CALLBACK_URL_SCHEMA
                                           andDelegate:self];
    }
    return _sinaWeibo;
}

- (void)sinaweiboDidLogIn:(SinaWeibo *)sinaweibo {
    SinaSSOViewController *sinaSSOViewController = [[SinaSSOViewController alloc] init];
    sinaSSOViewController.loginPlugin = self;
    [self.loginViewController presentViewController:sinaSSOViewController animated:YES completion:NULL];
    [self toCallBackSuccessWithCommand:self.sinaSSOCommand];
}

- (void)sinaweibo:(SinaWeibo *)sinaweibo logInDidFailWithError:(NSError *)error {
    [self toCallBackErrorWithCommand:self.sinaSSOCommand];
}

- (void)applicationWillEnterForeground:(NSNotification *)notification {
}

- (void)applicationDidBecomeActive:(NSNotification *)notification {
    [self.sinaWeibo applicationDidBecomeActive];
}


@end
