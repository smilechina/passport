//
//  SAPIRegisterPlugin.m
//  SAPIDemo
//
//  Created by Vinson.D.Warm on 13-9-26.
//  Copyright (c) 2013年 baidu. All rights reserved.
//

#import "SAPIRegisterPlugin.h"
#import <MessageUI/MFMessageComposeViewController.h>
#import "SAPILib.h"
#import "SAPIHudHelper.h"

#define SMS_RECIPIENT                   @"10690195092"

//#define SMS_RECIPIENT  @"106901954571+94"

#define TIMEOUT_INTERVAL                30

@interface SAPIRegisterPlugin () <MFMessageComposeViewControllerDelegate>

@property (nonatomic, assign) long reqStartTime;
@property (nonatomic, assign) NSInteger repeatCount;
@property (nonatomic, copy) NSString *smsContent;
@property (nonatomic, strong) NSTimer *checkTimer;

@end

@implementation SAPIRegisterPlugin

@synthesize smsContent = _smsContent;
@synthesize reqStartTime = _reqStartTime;
@synthesize repeatCount = _repeatCount;
@synthesize checkTimer = _checkTimer;
@synthesize webViewController = _webViewController;

- (void)action_fast_reg:(SAPIInvokeCommand *)command {
    if (!self.webViewController) return;
    BOOL canSendSMS = [MFMessageComposeViewController canSendText];
	if (canSendSMS) {
        self.smsContent = [NSString stringWithFormat:@"%@-%ld,发送即可注册", [self uuid], (long)[[NSDate date]timeIntervalSince1970]];
		MFMessageComposeViewController *picker = [[MFMessageComposeViewController alloc] init];
		picker.messageComposeDelegate = self;
		picker.navigationBar.tintColor = [UIColor blackColor];
		picker.body = self.smsContent;
		picker.recipients = [NSArray arrayWithObject:SMS_RECIPIENT];
        [self.webViewController presentViewController:picker animated:YES completion:NULL];
	} else {
        [[SAPIHudHelper getInstance] showHudOnWindow:@"本设备不支持上行短信注册" image:nil acitivity:NO autoHideTime:2.f];
    }
}

- (void)startCheck {
    [[SAPIHudHelper getInstance] showHudOnView:self.mainWebView caption:@"注册中" image:nil acitivity:YES autoHideTime:0.0]; 
    self.repeatCount = 30;
    if (self.checkTimer) [self.checkTimer invalidate];
    self.checkTimer = [NSTimer scheduledTimerWithTimeInterval:5.0f
                                                       target:self
                                                     selector:@selector(checkRegister)
                                                     userInfo:nil
                                                      repeats:YES];
}

- (void)stopCheck {
    [[SAPIHudHelper getInstance] hideHud];
    
    [self.checkTimer invalidate];
}

- (void)checkRegister {
    self.repeatCount -= 5;
    [[SAPIMainManager sharedManager].registerService registerAtOnceWithSMSContent:self.smsContent onCompletion:^(NSDictionary *info) {
        
        [self stopCheck];
        SAPILoginModel *model = [[SAPILoginModel alloc] initWithDictionary:info];
        [self.webViewController dismissViewControllerAnimated:YES completion:NULL];
        NSNotification *notification = [NSNotification notificationWithName:kRegistVerifiedNotification object:model userInfo:nil];
        [[NSNotificationCenter defaultCenter] postNotification:notification];
        
        [self.webViewController.navigationController popViewControllerAnimated:YES];
        
    } onError:^(NSDictionary *errorInfo) {
        
        NSInteger errNo = [[NSString stringWithFormat:@"%@", [errorInfo objectForKey:@"errno"] ]integerValue];
        if (errNo == 2) {
            
            if (self.repeatCount < 0) {
                [self stopCheck];
            }
        } else {
            
            [self stopCheck];
        }
        
    }];
}

// 处理发送完的响应结果
- (void)messageComposeViewController:(MFMessageComposeViewController *)controller didFinishWithResult:(MessageComposeResult)result
{
    if (result == MessageComposeResultCancelled) {
    }
    if (result == MessageComposeResultSent) {
        [self startCheck];
    }
    if(result == MessageComposeResultFailed) {
    }
    [controller dismissViewControllerAnimated:YES completion:NULL];
}

- (void)cancelAllRequest {
    [[SAPIMainManager sharedManager].registerService cancelRequest];
}

- (NSString*)uuid
{
    CFUUIDRef uuidRef = CFUUIDCreate(NULL);
    CFStringRef uuidStringRef= CFUUIDCreateString(NULL, uuidRef);
    
    CFRelease(uuidRef);
    NSString *uuid = [NSString stringWithString:(__bridge NSString*)uuidStringRef];
    
    CFRelease(uuidStringRef);
    return uuid;
}

@end
