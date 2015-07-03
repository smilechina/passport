//
//  SAPIForgetPwdPlugin.h
//  SAPIDemo
//
//  Created by Vinson.D.Warm on 4/1/14.
//  Copyright (c) 2014 baidu. All rights reserved.
//

#import "SAPIPlugin.h"

@interface SAPIForgetPwdPlugin : SAPIPlugin

@property (nonatomic, weak) UIViewController *webViewController;

- (void)action_forget_pwd:(SAPIInvokeCommand *)command;

@end


@interface SAPIForgetPwdViewController : UIViewController

@property (nonatomic, strong) NSURL *url;

- (id)initWithURL:(NSURL *)url;

@end