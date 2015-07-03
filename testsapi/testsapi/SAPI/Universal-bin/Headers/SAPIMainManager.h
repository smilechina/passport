//
//  SAPIMainManager.h
//  SAPIDemo
//
//  Created by Vinson.D.Warm on 13-9-5.
//  Copyright (c) 2013年 baidu. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "SAPILib.h"

@class SAPIMainManager;

@protocol SAPIMainManagerDelegate <NSObject>

@required
// 登录成功时调用
- (void)sapiManager:(SAPIMainManager *)sapiManager didLoginSucceed:(SAPILoginModel *)model;
// 登录失败
- (void)sapiManager:(SAPIMainManager *)sapiManager didLoginFail:(SAPILoginModel *)model;
// 补填用户名成功时调用
- (void)sapiManager:(SAPIMainManager *)sapiManager didFillUnameSucceed:(SAPILoginModel *)model;
// 注册成功时调用，此回调只会在上行短信注册成功时才会调用，其他通过webview注册的时候都是直接调用的登录成功。
- (void)sapiManager:(SAPIMainManager *)sapiManager didRegistVerified:(SAPILoginModel *)model;
// 第三方登录成功时调用
- (void)sapiManager:(SAPIMainManager *)sapiManager didOauthLoginSucceed:(SAPILoginModel *)model;
// 退出成功时调用
- (void)sapiManager:(SAPIMainManager *)sapiManager didLogOut:(SAPILoginModel *)model;

@optional
/**
 *  v6.7.4 新增
 *  静默互通登录成功时调用，仅供产品线用于统计静默互通
 *
 *  @param sapiManager SAPIMainManage
 *  @param options     可能包含有该静默帐号来源于哪个app的字段(sourceAppName)。
 */
- (void)sapiManager:(SAPIMainManager *)sapiManager silenceLoginSucceedWithOptions:(NSDictionary *)options;

/**
 *  v6.8.5 新增
 *  在成功登录一个帐号前会回调此方法
 *  目前仅会在通过v6.7.8新增的短信登录的接口来登录时，回调此方法。
 *
 *  @param sapiManager SAPIMainManage
 *  @param freshModel  将要登录成功的帐号信息
 */
- (void)sapiManager:(SAPIMainManager *)sapiManager beforeLoginSucceed:(SAPILoginModel *)freshModel;

@end

@interface SAPIMainManager : NSObject

// 基础配置参数
@property (nonatomic, assign) SapiEnvironmentType environmentType;
@property (nonatomic, copy) NSString* imei;
@property (nonatomic, copy) NSString* appid;
@property (nonatomic, copy) NSString* tpl;
@property (nonatomic, copy) NSString* appkey;
@property (nonatomic, copy) NSString* deviceIdEncryptKey;
@property (nonatomic, copy) NSString* packageSign;
@property (nonatomic, copy) NSString* appName;
@property (nonatomic, readonly) NSString* version;
@property (nonatomic, readonly) NSString* voiceProductId;
@property (nonatomic, assign) SAPIShareBindMode shareBindMode;

@property (nonatomic, assign) SAPILoginShareMode loginShareMode;
@property (nonatomic, assign) BOOL webNavigationBarHidden;
@property (nonatomic, assign) BOOL cacheEnabled;
@property (nonatomic, assign) BOOL deviceIdLoginForceReg;
@property (nonatomic, assign) BOOL oldDeviceTokenEnabled;
@property (nonatomic, assign) BOOL loginOptionHidden;
@property (nonatomic, assign) BOOL showFastRegLink;

// 快推登录/注册，开启快推登录、注册时登录、注册的帐号不支持互通
@property (nonatomic, assign) BOOL quickUserLogin;
@property (nonatomic, assign) BOOL quickUserSignUp;

// 关于声纹登录
@property (nonatomic, assign) BOOL showQuickLogin;
@property (nonatomic, copy) NSString *quickLoginUserName;
@property (nonatomic, assign) BOOL voicePrintLogining;

// 短信登录输入框默认手机号
@property (nonatomic, copy) NSString* inputPlaceholderPhoneNumber;
@property (nonatomic, copy) NSString* fastRegText;
@property (nonatomic, assign) BOOL showRegLink;
@property (nonatomic, assign) BOOL showIPlayout;

@property (nonatomic, strong) NSMutableArray *optionList;
@property (nonatomic, copy) NSString* skinUrl;

// 登录入口显示判断
@property (nonatomic, assign) BOOL showLoginLink; // 短信登录页面是否显示普通登录入口 1 显示  0 隐藏
@property (nonatomic, assign) BOOL showSMSLoginLink; // 普通登录界面是否显示短信登录入口 1 显示 0 隐藏
@property (nonatomic, assign) BOOL simplifyAccountNomailization; // 简化账号正常化

// 新浪微博、人人等通过oauth认证的第三方登录，每次登录都强制用户输入帐号密码来登录
@property (nonatomic, assign) BOOL isOauthForceLogin;

// 主登录界面URL
@property (nonatomic, readonly) NSURL *mainLoginUrl;
@property (nonatomic, readonly) NSURL *mainRegistUrl;
@property (nonatomic, readonly) NSURL *smsLoginUrl;

@property (nonatomic, strong, readonly) NSURL *enhancedShareLoginURL;

// 绑定相关URL
@property (nonatomic, readonly) NSURL *bindMobileUrl;
@property (nonatomic, readonly) NSURL *bindEmailUrl;
@property (nonatomic, readonly) NSURL *rebindMobileUrl;
@property (nonatomic, readonly) NSURL *rebindEmailUrl;
@property (nonatomic, readonly) NSURL *unbindMobileUrl;
@property (nonatomic, readonly) NSURL *unbindEmailUrl;
@property (nonatomic, readonly) NSURL *normalizeAccountUrl;
@property (nonatomic, readonly) NSURL *accountRecordIndexUrl;
@property (nonatomic, readonly) NSURL *changePasswordUrl;

// 登录接口URL
@property (nonatomic, readonly) NSString *sinaLoginUrl;
@property (nonatomic, readonly) NSString *qqLoginUrl;
@property (nonatomic, readonly) NSString *qqWeiboLoginUrl;
@property (nonatomic, readonly) NSString *renrenLoginUrl;
@property (nonatomic, readonly) NSString *sinaSSOLoginUrl;
@property (nonatomic, readonly) NSString *qrcodeLoginApp2PcUrl;
@property (nonatomic, readonly) NSString *qrcodeLoginPc2AppUrl;
@property (nonatomic, readonly) NSString *forgetPwdUrl;
@property (nonatomic, readonly) NSString *weixinLoginURLString;

// 强制绑定相关参数
@property (nonatomic, assign) BOOL connect;

// 执行绑定、解绑、换绑等功能成功后，是否跳过提示页面
@property (nonatomic, assign) BOOL quickCallbackAfterExecuteBind;

@property (nonatomic, strong) SAPILoginService *loginService;
@property (nonatomic, strong) SAPIRegisterService *registerService;

@property (nonatomic, weak) id<SAPIMainManagerDelegate> delegate;

// 乐彩登录、注册配置参数 v6.7.3新增
@property (nonatomic, assign) BOOL showLeCaiLogin;
@property (nonatomic, assign) BOOL showLeCaiRegTip;

/**
 *  v6.7.4 新增
 *  当产品线的App版本升级时，是否重新开启一次静默互通。
 *  此参数的设置只在App每个版本第一次启动时有效。
 *  默认为NO。
 */
@property (nonatomic, assign) BOOL silentShareOnUpgrade;

/**
 *  v6.7.6 新增
 *  是否支持无密码注册
 */
@property (nonatomic, assign) BOOL supportNoPwdRegister;

@property (nonatomic, copy) NSString *fastRegSMSChannel;

/**
 *  v6.8.4  新增
 *
 *  短信登录界面是否显示第三方登录入口
 */
@property (nonatomic, assign) BOOL showThirdLoginOnSMSLogin;

/**
 *  v6.8.4  新增
 *
 *  绑定手机时，如果手机号已经被绑定，是否跳转到短信登录界面
 *  如果设置为YES，则在绑定手机冲突时，如果用户点击了手机号登录则会回调SAPIControlPlugin的action_bind_widget_phone_number_exist:方法
 */
@property (nonatomic, assign) BOOL handleBindMobileConflict;

/**
 *  获取登录界面URL
 *
 *  @param loginType 普通登录或短信登录
 *  @param extra     需要额外传入的参数，以键值对形式传入，键、值类型均推荐采用NSString
 *
 *  @return 登录界面URL
 */
- (NSURL *)loginURLWithLoginType:(SAPILoginType)loginType extraParams:(NSDictionary *)extra;

// 当前登录Model，如果为nil,则当前没有登录账号
- (SAPILoginModel *)currentLoginModel;

// 登录帐号列表
- (NSArray *)localLoginModelList;

// 互通帐号列表
- (NSArray *)sharedLoginModelList;

// 设备号
- (NSString *)deviceToken;

/**
 *  用现有模型登录(含互通)
 *
 *  @param model 构造的model中如果uid、bduss、displayname任一参数为nil或空串，则会回调登录失败，其他情况会回调登录成
 *               功。
 */
- (void)loginWithLoginModel:(SAPILoginModel *)model;

// 清除所用快捷登录选项
- (void)clearLoginOptions;

// 添加快捷登录选项
- (void)addLoginOption:(SAPILoginOptionType)optionType;

// 取消当前SAPI所有网络请求
- (void)clearAllRequest;

// 云端同步 (回调)
- (void)syncCacheOnCompletion:(void (^)(void))completion error:(void (^)(void))error;

// 清除内存中缓存的登录页
- (void)clearCachePage;

// pass cookies可信任domain
- (NSArray *)getCookiesAuthorizedDomainList;

// 获取糯米强制绑定地址
- (NSURL *)enforceBindingURLWithToken:(NSString *)token
                               adtext:(NSString *)adtext
                               adhref:(NSString *)adhref
                            returnURL:(NSString *)returnURLStr;

// 获取强制绑定地址
- (NSURL *)accountBindingURLWithToken:(NSString *)token
                               adtext:(NSString *)adtext
                               adhref:(NSString *)adhref
                            returnURL:(NSString *)returnURLStr;

// 安全验证url
- (NSURL *)getAuthWidgetUrlWithToken:(NSString *)token
                           returnURL:(NSString *)returnUrl;

/**
 *  v6.7.8 新增
 *  重置静默互通状态
 *  重置后可以再次开启一次静默互通
 */
- (void)resetSilentShareLogin;

// 单例
+ (SAPIMainManager *)sharedManager;

@end
