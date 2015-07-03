//
//  BDSSpeakerRecognitionDelegate.h
//  BDSSpeakerRecognition
//
//  Created by 唐海员 on 14-6-12.
//  Copyright (c) 2014年 百度. All rights reserved.
//

#import <Foundation/Foundation.h>

@class BDSSpeakerRecognition;

@protocol BDSSpeakerRecognitionDelegate <NSObject>
@optional
/**
 * @brief 录音开始
 *
 * @param recognizer 识别器对象
 */
- (void)recordStart: (BDSSpeakerRecognition*)recognizer;

/**
 * @brief 录音结束
 *
 * @param recognizer 识别器对象
 */
- (void)recordFinish: (BDSSpeakerRecognition*)recognizer;

/**
 * @brief 开始上传用于注册的录音数据
 *
 * @param recognizer 识别器对象
 * @param idx 录音数据的对应的索引
 */
- (void)uploadSignUpAudioStart: (BDSSpeakerRecognition*)recognizer at: (NSInteger)idx;

/**
 * @brief idx对应的注册录音数据已上传完成
 *
 * @param recognizer 识别器对象
 * @param idx 录音数据对应的索引
 * @param err 返回本次上传的执行状态信息
 */
- (void)uploadSignUpAudioFinish: (BDSSpeakerRecognition*)recognizer at: (NSInteger)index result: (NSError*)err;

/**
 * @brief 开始上传验证的录音数据
 *
 * @param recognizer 识别器对象
 */
- (void)verifyStart: (BDSSpeakerRecognition*)recognizer;

/**
 * @brief 上传验证录音数据完成
 *
 * @param recognizer 识别器对象
 * @param err 返回本次上传的执行状态信息
 */
- (void)verifyFinish: (BDSSpeakerRecognition*)recognizer result: (NSError*)err;

/**
 * @brief 取消本次操作，停止所有工作
 *
 * @param recognizer 识别器对象
 */
- (void)cancel: (BDSSpeakerRecognition*)recognizer;

/**
 * @brief 识别器内部发生错误，停止工作
 *
 * @param recognizer 识别器对象
 * @param err 错误信息
 */
- (void)handleError: (BDSSpeakerRecognition*)recognizer error: (NSError*)err;
@end
