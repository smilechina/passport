//
//  SAPIQRCodeLoginPlugin.m
//  SAPIDemo
//
//  Created by Vinson.D.Warm on 12/2/13.
//  Copyright (c) 2013 baidu. All rights reserved.
//

#import "SAPIQRCodeLoginPlugin.h"
#import "SAPIQRCodeLoginViewController.h"

@implementation SAPIQRCodeLoginPlugin

@synthesize loginViewController = _loginViewController;

- (void)loginWithQRCode:(SAPIInvokeCommand *)command {
    SAPIQRCodeLoginViewController *qrcodeViewController = [[SAPIQRCodeLoginViewController alloc] initWithType:SAPIQRCodeLoginPCToApp];
    [self.loginViewController presentViewController:qrcodeViewController animated:YES completion:NULL];
    [self toCallBackSuccessWithCommand:command];
}

@end
