//
//  SAPIPlugin.h
//  SAPIBridge
//
//  Created by Vinson.D.Warm on 9/3/13.
//  Copyright (c) 2013 SAPI. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <UIKit/UIKit.h>
#import "SAPIInvokeCommand.h"

@interface SAPIPlugin : NSObject

@property (nonatomic, assign) BOOL runInBackground;
@property (nonatomic, weak) UIWebView *webView;

- (void)defaultCommand:(SAPIInvokeCommand *)command;

- (void)toCallBackSuccess:(NSDictionary *)result callBackId:(NSString *)callBackId;

- (void)toCallBackError:(NSDictionary *)result callBackId:(NSString *)callBackId;

- (void)toCallBackSuccessWithCommand:(SAPIInvokeCommand *)command;

- (void)toCallBackErrorWithCommand:(SAPIInvokeCommand *)command;

@end
