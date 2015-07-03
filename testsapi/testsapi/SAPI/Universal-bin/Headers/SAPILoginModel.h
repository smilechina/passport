//
//  SAPILoginModel.h
//  SAPILib
//
//  Created by Vinson.D.Warm on 13-9-5.
//  Copyright (c) 2013年 baidu. All rights reserved.
//

#import <Foundation/Foundation.h>

@interface SAPILoginModel : NSObject <NSCopying>

@property(nonatomic, copy) NSString* uname;             //登录后得到的uname
@property(nonatomic, copy) NSString* bduss;             //登录后得到的bduss (必须)
@property(nonatomic, copy) NSString* ptoken;            //登录后得到的ptoken (必须)
@property(nonatomic, copy) NSString* stoken;            //登录后得到的stoken
@property(nonatomic, copy) NSString* displayname;       //第3方登录返回displayname (必须)
@property(nonatomic, copy) NSString* uid;               //登录返回uid (必须)

/*
 oauthType :
 1 => 人人登录 Web
 2 => 新浪微博 Web
 4 => 腾讯微博 Web
 15 => Qzone登录 Web
 42 => 微信登录 Web
 */
@property(nonatomic, copy) NSString* oauthType;         //第3方登录端typeid

@property(nonatomic, copy) NSString* app;               //登录所在app的名称

@property (nonatomic, copy) NSString *os_headImgURLString; // 第三方登录用户头像地址

- (id)initWithDictionary:(NSDictionary *)loginSharedInfo;

- (NSDictionary *)toDictionary;

@end
