//
//  SAPIVoicePrintLoginPlugin.m
//  SAPIDemo
//
//  Created by Vinson.D.Warm on 7/7/14.
//  Copyright (c) 2014 baidu. All rights reserved.
//

#import "SAPIVoicePrintLoginPlugin.h"
#import "SAPIVoicePreLoginViewController.h"

@implementation SAPIVoicePrintLoginPlugin

- (void)action_voice_login:(SAPIInvokeCommand *)command {
    if (self.loginViewController) {
        SAPIVoicePreLoginViewController *preLoginVC =  [[SAPIVoicePreLoginViewController alloc] init];
        [self.loginViewController.navigationController pushViewController:preLoginVC animated:YES];
    }
}

@end
