//
//  SAPINavPlugin.h
//  SAPILib
//
//  Created by Vinson.D.Warm on 12/4/13.
//  Copyright (c) 2013 baidu. All rights reserved.
//

#import "SAPIPlugin.h"
#import "SAPIMainWebView.h"

@interface SAPINavPlugin : SAPIPlugin

@property (nonatomic, weak) UIViewController *webViewController;

- (void)back:(SAPIInvokeCommand *)command;

@end
