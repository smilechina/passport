//
//  SAPINavPlugin.m
//  SAPILib
//
//  Created by Vinson.D.Warm on 12/4/13.
//  Copyright (c) 2013 baidu. All rights reserved.
//

#import "SAPINavPlugin.h"

@implementation SAPINavPlugin

@synthesize webViewController = _webViewController;

- (void)back:(SAPIInvokeCommand *)command {
    if ([self.webViewController respondsToSelector:@selector(goBack:)]) {
        [self.webViewController performSelectorOnMainThread:@selector(goBack:) withObject:nil waitUntilDone:YES];
    }
}

@end
