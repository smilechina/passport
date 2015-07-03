//
//  SAPIEnforceBindingPlugin.m
//  SAPIDemo
//
//  Created by Vinson.D.Warm on 6/20/14.
//  Copyright (c) 2014 baidu. All rights reserved.
//

#import "SAPIAccountBindingPlugin.h"
#import "SAPIAccountBindingViewController.h"
#import "SAPILib.h"

@implementation SAPIAccountBindingPlugin

- (void)unite_verify_result:(SAPIInvokeCommand *)command {
    NSDictionary *dataInfo = command.paramsInfo;
    if (dataInfo && [dataInfo objectForKey:@"passuid"]) {
        SAPILoginModel *loginModel = [[SAPILoginModel alloc] initWithDictionary:dataInfo];
        loginModel.uid = [dataInfo objectForKey:@"passuid"];
        [[SAPIMainManager sharedManager] loginWithLoginModel:loginModel];
    }
}

- (NSString *)replaceUnicode:(NSString *)unicodeStr {
    NSString *tempStr1 = [unicodeStr stringByReplacingOccurrencesOfString:@"\\u" withString:@"\\U"];
    NSString *tempStr2 = [tempStr1 stringByReplacingOccurrencesOfString:@"\"" withString:@"\\\""];
    NSString *tempStr3 = [[@"\"" stringByAppendingString:tempStr2] stringByAppendingString:@"\""];
    NSData *tempData = [tempStr3 dataUsingEncoding:NSUTF8StringEncoding];
    NSString* returnStr = [NSPropertyListSerialization propertyListFromData:tempData
                                                           mutabilityOption:NSPropertyListImmutable
                                                                     format:NULL
                                                           errorDescription:NULL];
    return [returnStr stringByReplacingOccurrencesOfString:@"\\r\\n" withString:@"\n"];
}

@end
