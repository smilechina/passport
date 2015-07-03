//
//  BDSSpeakerRecognition.h
//  BDSSpeakerRecognition
//
//  Created by 唐海员 on 14-6-12.
//  Copyright (c) 2014年 百度. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "BDSSpeakerRecognitionDelegate.h"
#import "BDSSpeakerRecognitionDefine.h"


/**
 * @brief 日志级别枚举类型
 */
typedef enum BDSLogLevel {
    BDS_LOG_OFF = 0,
    BDS_LOG_ERROR = 1,
    BDS_LOG_WARN = 2,
    BDS_LOG_INFO = 3,
    BDS_LOG_DEBUG = 4,
    BDS_LOG_VERBOSE = 5,
} BDSLogLevel;


@interface BDSSpeakerRecognition : NSObject

/** 服务器地址 */
@property(nonatomic, copy) NSString* serverURL;
/** 产品id */
@property(nonatomic, copy) NSString* productID;
/** 用户id */
@property(nonatomic, copy) NSString* userID;
/** 识别结果的md5 */
@property(nonatomic, copy) NSString* recogResultMd5;
/** 语音识别结果（当用户所说语音与要求的text不匹配时，该字段会更新） */
@property(nonatomic, copy) NSString* recogResult;
/** 用户指定的用于生成注册字符串或者验证字符串的数字, 取值0到9的整数 */
@property(nonatomic) NSInteger luckyNumber;

/**
 * @brief 获取识别器识别器单例
 *
 *
 * @return 识别器唯一对象
 */
+ (BDSSpeakerRecognition*) shareInstance;

/**
 * @brief 释放识别器对象和资源
 *
 */
+ (void)releaseInstance;

/**
 * @brief 设置识别委托对象
 *
 */
- (void)setRecogDelegate: (id<BDSSpeakerRecognitionDelegate>)dlgt;

/**
 * @brief 重置注册信息，包括sn和注册字符串数组
 *
 */
- (void)resetSignUp;

/**
 * @brief 获取注册字符串条数
 *
 * @return 注册字符串条数
 */
- (NSInteger)signUpStringCount;

/**
 * @brief 获取某一条注册字符串
 *
 * @param idx string的索引
 *
 * @return 指定索引对应的字符串
 */
- (NSString*)singUpStringAt: (NSInteger)idx;

/**
 * @brief 重置验证，会重置验证字符串
 *
 */
- (void)resetVerify;

/**
 * @brief 获取验证字符串
 *
 * @return 当前的验证字符串
 */
- (NSString*)verifyString;

/**
 * @brief 注册，用户朗读一条注册字符串
 *
 * @param idx 注册字符串的索引
 * @param err 传出错误信息，如无错误，则为nil
 */
- (void)trySignUp: (NSInteger)idx error: (NSError**)err;

/**
 * @brief 验证，用户朗读一条验证字符串
 *
 * @param err 传出错误信息，如无错误，则为nil
 */
- (void)tryVerify: (NSError**)err;

/**
 * @brief 操作完成，停止录音
 *
 */
- (void)finishedTry;

/**
 * @brief 取消当前操作
 *
 */
- (void)cancelTry;

/**
 * @brief 获取版本号
 *
 */
- (NSString*)libVer;

/**
 * @brief 设置日志级别
 *
 * @param logLevel 日志级别
 */
+ (void)setLogLevel:(BDSLogLevel)logLevel;

/**
 * @brief 获取当前日志级别
 *
 * @return 日志级别
 */
+ (BDSLogLevel)logLevel;
@end
