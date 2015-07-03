//
//  SAPIDefine.h
//  SAPILib
//
//  Created by Vinson.D.Warm on 13-9-5.
//  Copyright (c) 2013年 baidu. All rights reserved.
//

#ifndef SAPILib_SAPIDefine_h
#define SAPILib_SAPIDefine_h

// 登录模式
typedef enum {
    SAPISilenceShareLoginMode = 2,
    SAPIChoiceShareLoginMode
} SAPILoginShareMode;

typedef enum {
    SAPIShareImplicitBindMode = 1,
    SAPIShareExplicitBindMode,
    SAPIShareOptionalBindMode
} SAPIShareBindMode;

// 快速登录选项
typedef enum {
    SAPILoginOptionTSina = 0,
    SAPILoginOptionTSinaSSO,
    SAPILoginOptionTQQ,
    SAPILoginOptionQzone,
    SAPILoginOptionQRCode,
    SAPILoginOptionDeviceLogin,
    SAPILoginOptionRenRen,
    SAPILoginOptionNuoMi,
    SAPILoginOptionVoicePrint,
    SAPILoginOptionWeiXinSSO,
} SAPILoginOptionType;

// 环境配置
typedef enum ESapiEnvironmentType
{
    SapiEnvironment_Online = 1,
    SapiEnvironment_RD,
    SapiEnvironment_QA
} SapiEnvironmentType;

//第3方登录相关操作返回errorcode信息
typedef enum
{
    //登录返回errorcode
    Oauth_TypeNotAvailable = 10,
    Oauth_InvalidOsuid = 17,
    Oauth_InvalidAct = 18,
    Oauth_InvalidAccessToken = 19,
    Oauth_AccessCancel = 501,
    Oauth_NoUserInfo = 502,
    Oauth_PassLoginFail = 401,
    Oauth_BindError = 901,
    Oauth_OtherError = -1,
    
    //帐号正常化返回errorcode
    Oauth_UserNoLogin = 119990
}TOauthErrorCode;

typedef NS_ENUM(NSInteger, SAPILoginType) {
    SAPILoginTypeDefault, // 普通登录
    SAPILoginTypeSMS, // 短信登录
};

typedef NS_ENUM(NSInteger, SAPILoginAccountType) {
    SAPILoginAccountTypeDefault = 0, // 默认情况
    SAPILoginAccountTypeMobile = 1, // 登录帐号类型为手机号码格式
    SAPILoginAccountTypeUsername = 2, // 登录帐号类型为用户名格式
};

//Service方法回调
typedef void (^SAPIRequestCompletionBlock)(NSDictionary *info);
typedef void (^SAPIRequestErrorBlock)(NSDictionary *errorInfo);

//登录相关Notification
// SAPI中相关行为所产生的Notification
//登陆成功消息 notification中的userInfo中会有登录成功后的json字典
#define kLoginSucceedNotification        @"kLoginSucceedNotification"

#define kUnsharedLoginSucceedNotification @"kUnsharedLoginSucceedNotification"

//登陆失败消息
#define kLoginFailNotification           @"kLoginFailNotification"

//注册验证成功消息 notification中的userInfo中会有注册成功后的json字典
#define kRegistVerifiedNotification      @"kRegistVerifiedNotification"

//补填用户名成功消息 notification中的userInfo中会有注册成功后的json字典
//返回json数据包含
#define kFillUnameSucceedNotification    @"kFillUnameSucceedNotification"

//第3方页面登录返回信息
#define kOauthLoginNotification          @"kOauthLoginNotification"

//帐号完整化返回信息
#define kFillAccountNotification         @"kFillAccountNotification"

//退出返回信息
#define kLogOutNotification              @"kLogOutNotification"

#endif
