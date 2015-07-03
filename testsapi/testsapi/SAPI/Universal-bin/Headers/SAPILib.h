//
//  SAPILib.h
//  SAPILib
//
//  Created by Vinson.D.Warm on 13-9-6.
//  Copyright (c) 2013年 baidu. All rights reserved.
//
//  v6.11.2 2015.06.01
//  取消导入登录态时ptoken不能为nil的限制；新增一个获取登录界面URL的方法；优化代码
//
//  v6.11.1 2015.05.18
//  支持线下环境SDK版本号检测；修复声纹登录帐号无法互通的问题
//
//  v6.11.0 2015.05.12
//  声纹登录带*方案
//
//  v6.8.5  2015.05.05
//  SAPIMainManagerDelegate新增成功登录前的回调
//
//  v6.8.4  2015.04.30
//  短信登录增加第三方登录入口；优化手机绑定逻辑
//
//  v6.8.3  2015.04.27
//  优化bduss、cookie的处理策略
//
//  v6.8.2  2015.04.21
//  新增错误码定义；优化帐号正常化逻辑

#ifndef SAPILib_SAPILib_h
#define SAPILib_SAPILib_h

// 工具 & 框架
#import "SAPIJSONUtility.h"
#import "SAPIInvokeCommand.h"
#import "SAPIPlugin.h"
#import "SAPIWebView.h"
#import "SAPIMainWebView.h"
#import "SapiUIDManager.h"

// SAPI基本类型定义
#import "SAPIDefine.h"

// SAPI通用模型
#import "SAPILoginModel.h"

// SAPI管理组件
#import "SapiError.h"
#import "SAPILoginService.h"
#import "SAPIRegisterService.h"
#import "SAPIMainManager.h"

#endif
