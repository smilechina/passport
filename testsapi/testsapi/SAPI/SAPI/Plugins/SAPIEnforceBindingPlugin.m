//
//  SAPIEnforceBindingPlugin.m
//  SAPIDemo
//
//  Created by Vinson.D.Warm on 6/20/14.
//  Copyright (c) 2014 baidu. All rights reserved.
//

#import "SAPIEnforceBindingPlugin.h"
#import "SAPIEnforceBindingViewController.h"
#import "SAPILib.h"

@implementation SAPIEnforceBindingPlugin

- (void)action_unite_verify:(SAPIInvokeCommand *)command {
    NSString *resultStr = [command.paramsInfo objectForKey:@"result"];
    NSDictionary *result = [SAPIJSONUtility objectFromJSONString:resultStr];
    if (result) {
        NSString *adtext = [result objectForKey:@"adtext"];
        NSString *adhref = [result objectForKey:@"adhref"];
        NSString *token = [result objectForKey:@"token"];
        if (self.webViewController) {
            NSURL *bindingURL = [[SAPIMainManager sharedManager] enforceBindingURLWithToken:token
                                                                                     adtext:adtext
                                                                                     adhref:adhref
                                                                                  returnURL:@"http://www.baidu.com"];
            SAPIEnforceBindingViewController *enforceBindingVC = [[SAPIEnforceBindingViewController alloc] initWithURL:bindingURL];
            [self.webViewController.navigationController pushViewController:enforceBindingVC animated:YES];
        }
    }
    
    [self toCallBackSuccessWithCommand:command];
}

- (void)unite_verify_result:(SAPIInvokeCommand *)command {
    NSDictionary *dataInfo = command.paramsInfo;
    NSString *passuid = [dataInfo objectForKey:@"passuid"];
    if (dataInfo && passuid.length) {
        SAPILoginModel *loginModel = [[SAPILoginModel alloc] initWithDictionary:dataInfo];
        loginModel.uid = passuid;
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
