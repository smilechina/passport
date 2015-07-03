//
//  SAPILoginService.h
//  SAPILib
//
//  Created by Vinson.D.Warm on 13-9-8.
//  Copyright (c) 2013年 baidu. All rights reserved.
//

#import <Foundation/Foundation.h>

@class SAPILoginModel;
@class SAPIVoiceInfo;

@interface SAPILoginService : NSObject

- (void)clearLoginDeviceToken;

// 设备号登录
- (void)loginWithDeviceIdOnCompletion:(SAPIRequestCompletionBlock)completionBlock
                              onError:(SAPIRequestErrorBlock)errorBlock;

// 判断model是否来自设备号登录
- (BOOL)modelFromDeviceLogin:(SAPILoginModel *)model;

// app to pc 登录确认
- (BOOL)confirmLoginWithAppToPCWithCmd:(NSString *)cmd
                                  sign:(NSString *)sign
                          onCompletion:(SAPIRequestCompletionBlock)completionBlock
                               onError:(SAPIRequestErrorBlock)errorBlock;

// app to pc 登录
- (void)loginFromAppToPCwithLoginModel:(SAPILoginModel *)loginModel
                                   cmd:(NSString *)cmd
                                  sign:(NSString *)sign
                          onCompletion:(SAPIRequestCompletionBlock)completionBlock
                               onError:(SAPIRequestErrorBlock)errorBlock;

// pc to app 登录
- (void)loginFromPCToAppWithCmd:(NSString *)cmd
                           sign:(NSString *)sign
                   onCompletion:(SAPIRequestCompletionBlock)completionBlock
                        onError:(SAPIRequestErrorBlock)errorBlock;

// 短信登录：发送短信验证码
- (BOOL)loginGetDypassWithPhoneNumber:(NSString *)phoneNum
                         onCompletion:(SAPIRequestCompletionBlock)completionBlock
                              onError:(SAPIRequestErrorBlock)errorBlock;

// 短信登录：用短信验证码登录
- (BOOL)loginWithDypass:(NSString *)dypass
            phoneNumber:(NSString *)phoneNum
           onCompletion:(SAPIRequestCompletionBlock)completionBlock
                onError:(SAPIRequestErrorBlock)errorBlock;

// 修改头像
- (BOOL)uploadPortrait:(NSData *)imageData
              mimeType:(NSString *)mimeType
            loginModel:(SAPILoginModel *)model
          onCompletion:(SAPIRequestCompletionBlock)completionBlock
               onError:(SAPIRequestErrorBlock)errorBlock;

// 获取头像
- (BOOL)getPortraitInfo:(SAPILoginModel *)model
           onCompletion:(SAPIRequestCompletionBlock)completionBlock
                onError:(SAPIRequestErrorBlock)errorBlock;

// 补填用户名
- (BOOL)fillUname:(NSString *)uname
       loginModel:(SAPILoginModel *)model
     onCompletion:(SAPIRequestCompletionBlock)completionBlock
          onError:(SAPIRequestErrorBlock)errorBlock;

// 获取voice id (用户名)
- (BOOL)getVoiceUidWithUserName:(NSString *)username
                        isPhone:(BOOL)isPhone
                        isMerge:(BOOL)merge
                   onCompletion:(SAPIRequestCompletionBlock)completionBlock
                        onError:(SAPIRequestErrorBlock)errorBlock;

// 获取voice id (用bduss)
- (BOOL)getVoiceUidWithBduss:(NSString *)bduss
                onCompletion:(SAPIRequestCompletionBlock)completionBlock
                     onError:(SAPIRequestErrorBlock)errorBlock;

// 声纹注册
- (BOOL)signUpWithVoiceHash:(NSString *)hash
                    authsid:(NSString *)authsid
                      bduss:(NSString *)bduss
                  isNewUser:(BOOL)newUser
               onCompletion:(SAPIRequestCompletionBlock)completionBlock
                    onError:(SAPIRequestErrorBlock)errorBlock;

// 声纹登录
- (BOOL)loginWithVoiceHash:(NSString *)hash
               encryptedId:(NSString *)encryptedId
              onCompletion:(SAPIRequestCompletionBlock)completionBlock
                   onError:(SAPIRequestErrorBlock)errorBlock;

// 密码校验（修改声纹前）

//======== 声纹加星改版，重新设计接口
/**
 *  通过bduss获取Voice Id，信息通过SAPIVoiceInfo返回给产品线，产品线需要自行管理。
 *
 *  @param bduss   用户bduss
 *  @param success 成功时回调
 *  @param failure 失败时回调
 */
- (void)getVoiceUidWithBduss:(NSString *)bduss
                     success:(void (^)(SAPIVoiceInfo *voiceInfo))success
                     failure:(void (^)(NSError *error))failure;

/**
 *  通过用户名获取Voice Id，信息通过SAPIVoiceInfo返回给产品线，产品线需要自行管理。
 *
 *  @param username 用户名
 *  @param isPhone  是否为手机号
 *  @param merge    是否为合并帐号
 *  @param success  成功时回调
 *  @param failure  失败时回调
 */
- (void)getVoiceUidWithUserName:(NSString *)username
                        isPhone:(BOOL)isPhone
                        isMerge:(BOOL)merge
                        success:(void (^)(SAPIVoiceInfo *voiceInfo))success
                        failure:(void (^)(NSError *error))failure DEPRECATED_MSG_ATTRIBUTE("replaced by getVoiceUidWithUserName:accountType:success:failure:");

/**
 *  通过用户名获取Voice Id
 *
 *  @param username    用户名
 *  @param accountType 帐号类型
 *  @param success     查询成功时的回调
 *  @param failure     查询失败时的回调
 */
- (void)getVoiceUidWithUserName:(NSString *)username
                    accountType:(SAPILoginAccountType)accountType
                        success:(void (^)(SAPIVoiceInfo *voiceInfo))success
                        failure:(void (^)(NSError *error))failure;

/**
 *  声纹注册
 *
 *  @param hash    语音Hash字符串
 *  @param authsid 授权id
 *  @param bduss   用户bduss
 *  @param newUser 是否为用户
 *  @param success 成功时回调
 *  @param failure 失败时回调
 */
- (void)signUpWithVoiceHash:(NSString *)hash
                    authsid:(NSString *)authsid
                      bduss:(NSString *)bduss
                  isNewUser:(BOOL)newUser
                    success:(void (^)(SAPILoginModel *loginModel))success
                    failure:(void (^)(NSError *error))failure;
/**
 *  声纹登录
 *
 *  @param hash        语音Hash字符串
 *  @param encryptedId 用户加密Id
 *  @param success     成功时回调
 *  @param failure     失败时回调
 */
- (void)loginWithVoiceHash:(NSString *)hash
               encryptedId:(NSString *)encryptedId
                   success:(void (^)(SAPILoginModel *loginModel))success
                   failure:(void (^)(NSError *error))failure;
/**
 *  更新密保数字
 *
 *  @param bduss   用户bduss
 *  @param success 成功时回调
 *  @param failure 失败时回调
 */
- (void)updateVoiceLuckNumber:(NSInteger) luckNumber
                        bduss:(NSString *)bduss
                      success:(void (^)(void))success
                      failure:(void (^)(NSError *error))failure;
/**
 *  用现有模型登录(含互通)
 *
 *  @param model 构造的model中如果uid、bduss、displayname任一参数为nil或空串，则会回调登录失败，其他情况会回调登录成
 *               功。
 */
- (void)loginWithLoginModel:(SAPILoginModel *)model;

/**
 *  用现有模型登录(不含互通)
 *  建议以下情况使用：
 *  1. web端登录状态同步到sdk里
 *  2. 兼容历史版本登录状态
 *
 *  @param model 构造的model中如果uid、bduss、displayname、ptoken任一参数为nil，则会回调登录失败，其他情况会回调登录成
 *               功；产品线没有ptoken参数的时候，ptoken可传空字符串，但uid、bduss、displayname不能为空。
 */
- (void)unsharedLoginWithLoginModel:(SAPILoginModel *)model;

// 退出
- (BOOL)logout:(SAPILoginModel *)model;

// 重登录
- (BOOL)reloginWithUid:(NSString *)uid
          onCompletion:(void (^)(void))completion
                 error:(void (^)(void))error DEPRECATED_MSG_ATTRIBUTE("replaced by reloginWithUid:success:failure:");

/**
 *  利用本地可能存在的登录信息来尝试重登录（第三方登录帐号不支持重登录）
 *  替代reloginWithUid:onCompletion:error:接口
 *
 *  @param uid     重登录用户的uid
 *  @param success 重登录成功时的回调，会返回一个SAPILoginModel实例
 *  @param failure 重登录失败时的回调，会返回一个NSError实例
 */
- (void)reloginWithUid:(NSString *)uid
               success:(void (^)(SAPILoginModel *model))success
               failure:(void (^)(NSError *error))failure;

/**
 *  根据bduss同步loginModel到sdk（此接口同步的帐号不会互通），需网络请求
 *
 *  @param bduss           bduss
 *  @param ptoken          ptoken，不能为nil，没有时可传入空字符串
 *  @param app             帐号来源app名字，不能为nil，没有时可传入空字符串
 *  @param completionBlock 同步成功时的回调
 *  @param errorBlock      同步失败时的回调
 *
 *  @return 传入参数格式是否正确，返回NO表示传入参数不合法
 */
- (BOOL)syncLoginModelWithBduss:(NSString *)bduss
                         ptoken:(NSString *)ptoken
                            app:(NSString *)app
                   onCompletion:(SAPIRequestCompletionBlock)completionBlock
                        onError:(SAPIRequestErrorBlock)errorBlock;


// 获取登录行为信息
- (NSDictionary *)readLoginActionInfoByUid:(NSString *)uid;

/**
 *  获取用户信息
 *
 *  @param bduss           用户的bduss
 *
 *
 *  @param completionBlock 获取成功时的回调。可能包含以下字段：
 *                          displayname：用户显示名称，用于产品线展示。
 *
 *                          have_psw：是否设置了密码。
 *
 *                          incomplete_user：是否为半帐号。为1时即为半帐号，半帐号需要绑定手机或者正常化后才能调用其他接口。
 *
 *                          portrait：头像地址拼接串。
 *                          portrait_tag：头像id的md5值，为 0 时表示用户尚未设置头像。
 *                          可根据portrait和portrait_tag拼接出头像地址：
 *                          NSString *portraitUrl = [NSString stringWithFormat:@"http://himg.bdimg.com/sys/portrait/item/%@.jpg?%@", [info objectForKey:@"portrait"], [info objectForKey:@"portrait_tag"]];
 *
 *                          secureemail：打码后的邮箱，用户已绑定邮箱时会返回此字段。
 *
 *                          securemobil：打码后的手机，用户已绑定手机时会返回此字段。
 *
 *                          userid：用户id。
 *
 *                          username：用户名（可能为空）。显示用户名请使用displayname字段。
 *
 *
 *  @param errorBlock      获取失败时的回调。最常见的错误情况为传入bduss已失效,此时返回errno:400021，errmsg: "user not
 *                          online, status = 2"
 *
 *  @return 传入bduss为空时返回NO，其他返回YES
 *
 */
- (BOOL)getUserInfo:(NSString *)bduss
       onCompletion:(SAPIRequestCompletionBlock)completionBlock
            onError:(SAPIRequestErrorBlock)errorBlock;

// 用加密密码和 uid 登录
- (BOOL)loginWithUid:(NSString *)uid
       encryptedPass:(NSString *)pass
        onCompletion:(SAPIRequestCompletionBlock)completionBlock
             onError:(SAPIRequestErrorBlock)errorBlock;

// 百度公用rsa加密
- (BOOL)bdRSAEncrypt:(NSString *)srcStr
        onCompletion:(SAPIRequestCompletionBlock)completionBlock
             onError:(SAPIRequestErrorBlock)errorBlock;

/**
 *  获取用户历史头像列表
 *
 *  v6.7.0新增
 *
 *  @param bduss           bduss
 *  @param count           获取数量
 *  @param completionBlock 获取成功时回调
 *  @param errorBlock      获取失败时回调
 */
- (void)getUserHistoricalAvatarWithBduss:(NSString *)bduss
                                   count:(NSUInteger)count
                            onCompletion:(SAPIRequestCompletionBlock)completionBlock
                                 onError:(SAPIRequestErrorBlock)errorBlock;

/**
 *  获取热门推荐头像列表
 *
 *  v6.7.0新增
 *
 *  @param bduss           bduss
 *  @param completionBlock 获取成功时回调
 *  @param errorBlock      获取失败时回调
 */
- (void)getHotAvatarListWithBduss:(NSString *)bduss
                     onCompletion:(SAPIRequestCompletionBlock)completionBlock
                          onError:(SAPIRequestErrorBlock)errorBlock;

/**
 *  设置用户头像为热门推荐头像的某个头像 (与用户自定义修改头像的接口不同，请注意区分)
 *
 *  v6.7.0新增
 *
 *  @param bduss           bduss
 *  @param serie           所选热门头像的系列
 *  @param number          所选热门头像的序号
 *  @param completionBlock 设置成功时的回调
 *  @param errorBlock      设置失败时的回调
 */
- (void)setHotAvatarWithBduss:(NSString *)bduss
                        serie:(NSString *)serie
                       number:(NSUInteger)number
                 onCompletion:(SAPIRequestCompletionBlock)completionBlock
                      onError:(SAPIRequestErrorBlock)errorBlock;

/**
 *  微信登录时先获取mkey防止csrf攻击
 *  v6.7.1新增
 *
 *  @param wxAppId         微信的AppId
 *  @param scope           微信的授权范围，默认请填写snsapi_userinfo
 *  @param bindType        与第三方帐号的绑定类型：implicit－暗绑，explicit－明绑，optional－选择性绑定
 *  @param completionBlock 获取成功时的回调，成功时会返回一个mkey字段，请作为参数传入微信登录的state字段
 *  @param errorBlock      获取失败时的回调
 */
- (void)getMkeyWithWeiXinAppId:(NSString *)wxAppId
                         scope:(NSString *)scope
                      bindType:(NSString *)bindType
                  OnCompletion:(SAPIRequestCompletionBlock)completionBlock
                       onError:(SAPIRequestErrorBlock)errorBlock;

/**
 *  根据用户名、明文密码尝试重登录（仅支持百度帐号，第三方帐号不支持重登录）
 *  仅在没有触发反作弊、用户帐号类型不明确等各类其他情况时才能重登录成功
 *  没有用户名、明文密码或已接入SAPI SDK登录的帐号，可调用reloginWithUid:success:failure:接口来尝试重登录
 *
 *  v6.7.7新增
 *
 *  @param username 用户名
 *  @param password 明文密码
 *  @param success  登录成功时的回调，返回一个SAPILoginModel实例
 *  @param failure  登录失败时的回调，返回一个NSError实例,其中domain为错误文案，code为错误码
 */
- (void)reloginWithUsername:(NSString *)username
                   password:(NSString *)password
                    success:(void (^)(SAPILoginModel *loginModel))success
                    failure:(void (^)(NSError *error))failure;

/**
 *  通过手机号获取动态密码，然后根据手机号、动态密码登录
 *
 *  v6.7.8新增
 *
 *  @param mobile  手机号
 *  @param success 获取成功时的回调，返回一个内容格式如@{ @"errCode": @"0", @"errMsg": @"" }的键值对
 *  @param failure 获取失败时的回调，返回一个NSError实例,其中domain为错误文案，code为错误码
 */
- (void)getDpassWithMobile:(NSString *)mobile
                   success:(void (^)(NSDictionary *info))success
                   failure:(void (^)(NSError *error))failure;

/**
 *  根据手机号、动态密码登录
 *  先调用getDpassWithMobile:success:failure:接口获取动态密码
 *
 *  v6.7.8新增
 *
 *  @param mobile  手机号
 *  @param dpass   动态密码，通过getDpassWithMobile:success:failure:获取
 *  @param success 登录成功时的回调，返回一个SAPILoginModel实例
 *  @param failure 登录失败时的回调，返回一个NSError实例,其中domain为错误文案，code为错误码
 */
- (void)loginWithMobile:(NSString *)mobile
                  dpass:(NSString *)dpass
                success:(void (^)(SAPILoginModel *loginModel))success
                failure:(void (^)(NSError *error))failure;

/**
 *  生成短信内容，用于上行短信注册、登录等操作
 *
 *  v6.7.8新增
 *
 *  @return 生成的短信内容
 */
- (NSString *)getUpwardSMSContentForRegister;

/**
 *  通过上行短信注册并登录帐号
 *  需先调用getUpwardSMSContentForRegister接口获取短信内容并成功发送该短信后再调用本接口
 *
 *  v6.7.8新增
 *
 *  @param sms     上行短信的内容，通过getUpwardSMSContentForRegister接口获取
 *  @param timeout 本次注册、登录操作的超时时间
 *  @param success 注册并登录成功时的回调，返回一个SAPILoginModel实例
 *  @param failure 注册、登录失败时的回调，返回一个NSError实例
 */
- (void)registerBySendSMS:(NSString *)sms
                  timeout:(NSTimeInterval)timeout
                  success:(void (^)(SAPILoginModel *loginModel))success
                  failure:(void (^)(NSError *error))failure;

- (NSString *)getVoiceAESKey;

- (void)clearAllRequest;

@end
