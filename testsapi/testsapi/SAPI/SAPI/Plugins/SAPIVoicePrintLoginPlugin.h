//
//  SAPIVoicePrintLoginPlugin.h
//  SAPIDemo
//
//  Created by Vinson.D.Warm on 7/7/14.
//  Copyright (c) 2014 baidu. All rights reserved.
//

#import "SAPIPlugin.h"

@interface SAPIVoicePrintLoginPlugin : SAPIPlugin

@property (nonatomic, weak) UIViewController *loginViewController;

- (void)action_voice_login:(SAPIInvokeCommand *)command;

@end
