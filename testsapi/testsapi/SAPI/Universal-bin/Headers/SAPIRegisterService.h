//
//  SAPIRegisterService.h
//  SAPILib
//
//  Created by Vinson.D.Warm on 13-9-26.
//  Copyright (c) 2013年 baidu. All rights reserved.
//

@interface SAPIRegisterService : NSObject

// 快速注册
- (void)registerAtOnceWithSMSContent:(NSString *)smsContent
                        onCompletion:(SAPIRequestCompletionBlock)completionBlock
                             onError:(SAPIRequestErrorBlock)errorBlock;

- (void)cancelRequest;

@end
