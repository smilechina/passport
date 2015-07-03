//
//  SAPIControlPlugin.h
//  SAPIDemo
//
//  Created by Vinson.D.Warm on 12/4/13.
//  Copyright (c) 2013 baidu. All rights reserved.
//
//  SAPIControlPlugin属于基础控件，必须导入产品线工程
//  SAPIControlPlugin下的- (void)finish:(SAPIInvokeCommand *)command;方法，
//  主要用于触发登录界面webview的左上角“返回”按钮，以及响应其他情况下关闭webview时的事情。
//  在Demo中SAPILoginViewController是被push进navigation stack来呈现的，
//  所以- (void)finish:(SAPIInvokeCommand *)command;中调用的是pop方法
//  产品线如果想采用present的方法来呈现SAPILoginViewController，则finish:中应相应的采用dismiss方法

#warning 此plugin必须导入

#import "SAPIPlugin.h"

@interface SAPIControlPlugin : SAPIPlugin

@property (nonatomic, weak) UIViewController *webViewController;

// 点击“返回”按钮时
- (void)finish:(SAPIInvokeCommand *)command;

/**
 *  绑定手机时，如果该手机已被绑定，同时配置[SAPIMainManager sharedManager].handleBindMobileConflict为YES，
 *  在用户点击“手机号登录”选项时则会回调此方法。
 *
 *  @param command 回传参数，paramsInfo包含有用户输入的手机号。
 */
- (void)action_bind_widget_phone_number_exist:(SAPIInvokeCommand *)command;

@end
