//
//  BDSSpeakerRecognitionDefine.h
//  BDSSpeakerRecognition
//
//  Created by 唐海员 on 14-6-12.
//  Copyright (c) 2014年 百度. All rights reserved.
//

// 程序版本
FOUNDATION_EXPORT NSString* const BDS_VERSION_NAME;
    
/** 识别器错误域 */
FOUNDATION_EXPORT NSString * const BDS_ERR_DOMAIN_RECOGNITION;
typedef enum BDSErrRecognition {
    BDS_RECOGNITION_SUCCESS = 0,            // 成功
    BDS_ERR_RECORDER_UNAVAILABLE = 1001,    // 录音机不可用, 需要检查应用程序是否有录音权限
    BDS_ERR_RECORDER_BUSY = 1002,           // 录音机繁忙, 上次录音还未结束
    BDS_ERR_USER_IDENTITY_NOT_SET = 2001,   // 没有设置user id
    BDS_ERR_PRODUCT_ID_NOT_SET = 2002,      // 没有设置product id
    BDS_ERR_INDEX_OUT_OF_BOUNDS = 2003,     // 获取注册字串，或者执行注册的次数超出限制
    BDS_ERR_SIGNUP_NOT_INITED = 2004,       // 注册流程未初始化
    BDS_ERR_ENCODE_AUDIO = 2005,            // 录音数据编码失败
    BDS_ERR_PREPARE_PARAMS = 2006           // 准备识别参数失败
}BDSErrRecognition;

/** 录音机错误域 */
FOUNDATION_EXPORT NSString * const BDS_ERR_DOMAIN_RECORDER;
typedef enum BDSErrRecorder {
    BDS_RECORDER_OK = 0,                    // 成功
    BDS_RECORDER_NO_PERMISSION = 2201,      // 没有录音权限
    // 其他录音机域的错误码为audio queue的错误码
}BDSErrRecorder;

/** 网络交互错误域 */
FOUNDATION_EXPORT NSString* const BDS_ERR_DOMAIN_NETWORK;
typedef enum BDSErrNetwork {
    BDS_NETWORK_OK = 0,                     // 成功
    BDS_ERROR_RESPONSE_PARSE_ERROR = 2101,  // 解析服务器响应数据失败
    BDS_ERROR_HTTP_STATUS_ERROR = 2102,     // http错误
    BDS_ERROR_VERIFY_NO_PASSED = 2103,      // 验证未通过
    // 其他网络交互域的错误码为服务器后端错误码
    BDS_ERROR_RECOG_RESULT_NOT_MATCH = -3009, // 识别结果与文本不匹配
}BDSErrNetwork;

/** 服务器地址 */
FOUNDATION_EXPORT NSString * const BDS_SERVER_URL;
FOUNDATION_EXPORT NSString * const BDS_HTTP_CONTENT_TYPE_VALUE;
FOUNDATION_EXPORT NSString * const BDS_HTTP_CONTENT_TYPE_KEY;
FOUNDATION_EXPORT NSString * const BDS_HTTP_BOUNDARY;

// request param
FOUNDATION_EXPORT NSString* const BDS_REQUEST_PARAM_PLATFORM;
FOUNDATION_EXPORT NSString* const BDS_REQUEST_PARAM_DEVICE;
FOUNDATION_EXPORT NSString* const BDS_REQUEST_PARAM_VERSION;
FOUNDATION_EXPORT NSString* const BDS_REQUEST_PARAM_USER_ID;
FOUNDATION_EXPORT NSString* const BDS_REQUEST_PARAM_PRODUCT_ID;
FOUNDATION_EXPORT NSString* const BDS_REQUEST_PARAM_PROTOCOL;
FOUNDATION_EXPORT NSString* const BDS_REQUEST_PARAM_SERIAL_NUMBER;
FOUNDATION_EXPORT NSString* const BDS_REQUEST_PARAM_SESSION_ID;
FOUNDATION_EXPORT NSString* const BDS_REQUEST_PARAM_INDEX;
FOUNDATION_EXPORT NSString* const BDS_REQUEST_PARAM_TEXT;
FOUNDATION_EXPORT NSString* const BDS_REQUEST_PARAM_FUNCTION;
FOUNDATION_EXPORT NSString* const BDS_REQUEST_PARAM_RETURN_TYPE;
FOUNDATION_EXPORT NSString* const BDS_REQUEST_PARAM_RESERVE;
FOUNDATION_EXPORT NSString* const BDS_REQUEST_PARAM_USER;
FOUNDATION_EXPORT NSString* const BDS_REQUEST_PARAM_ENC;

// response define
FOUNDATION_EXPORT NSString* const BDS_JSON_KEY_RESULT;
FOUNDATION_EXPORT NSString* const BDS_JSON_KEY_SN;
FOUNDATION_EXPORT NSString* const BDS_JSON_KEY_INDEX;
FOUNDATION_EXPORT NSString* const BDS_JSON_KEY_ERROR_NO;
FOUNDATION_EXPORT NSString* const BDS_JSON_KEY_ERROR_MSG;
FOUNDATION_EXPORT NSString* const BDS_JSON_KEY_RECOG_STR;
FOUNDATION_EXPORT NSString* const BDS_JSON_KEY_SPEAKER;
FOUNDATION_EXPORT NSString* const BDS_JSON_KEY_SPEAKER_VERIFY;
FOUNDATION_EXPORT NSString* const BDS_JSON_KEY_MD5;

FOUNDATION_EXPORT NSInteger const BDS_SIGN_UP_STRING_COUNT;
FOUNDATION_EXPORT NSInteger const BDS_SIGN_UP_STRING_LENGTH;
FOUNDATION_EXPORT NSInteger const BDS_VERIFY_STRING_LENGTH;

FOUNDATION_EXPORT NSInteger const BDS_AUDIO_RECORD_SECONDS;