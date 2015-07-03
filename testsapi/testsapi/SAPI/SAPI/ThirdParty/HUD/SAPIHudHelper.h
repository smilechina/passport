//
//  SAPIHudHelper.h
//  RenrenSixin
//
//  Created by  on 12-2-24.
//  Copyright (c) 2012年 renren. All rights reserved.
//
#define RS_HUD_ICON_OK              [UIImage imageNamed:@"hud_icon_ok"]
#define RS_HUD_ICON_WARNING         [UIImage imageNamed:@"hud_icon_error"]

#import <Foundation/Foundation.h>
#import <UIKit/UIKit.h>
#import "ATMHud.h"

#define DEFAULTTIME 2.0f//用于atmhud统一autohidetime
@interface SAPIHudHelper : NSObject
{
    ATMHud*  _hud;
}

@property (nonatomic, retain) ATMHud* hud;

// 单例
+ (SAPIHudHelper*) getInstance;

// 在window上显示hud
// 参数：
// caption:标题 
// bActive：是否显示转圈动画
// time：自动消失时间，如果为0，则不自动消失

- (void)showHudOnWindow:(NSString*)caption 
                  image:(UIImage*)image
              acitivity:(BOOL)bAcitve
           autoHideTime:(NSTimeInterval)time;
// 在当前的view上显示hud
// 参数：
// view：要添加hud的view
// caption:标题 
// image:图片
// bActive：是否显示转圈动画
// time：自动消失时间，如果为0，则不自动消失
- (void)showHudOnView:(UIView*)view 
              caption:(NSString*)caption
                image:(UIImage*)image
            acitivity:(BOOL)bAcitve
         autoHideTime:(NSTimeInterval)time;


- (void)showHudOnView:(UIView*)view
              caption:(NSString*)caption
                image:(UIImage*)image
            acitivity:(BOOL)bAcitve
         autoHideTime:(NSTimeInterval)time
               target:(id)aTarget
             selector:(SEL)aSelector;


- (void)showProgressHudOnView:(UIView*)view
                      caption:(NSString*)caption
                        image:(UIImage*)image
                    acitivity:(BOOL)bAcitve
                 autoHideTime:(NSTimeInterval)time;

- (void)showDownloadProgressHudOnView:(UIView*)view
                      caption:(NSString*)caption
                        image:(UIImage*)image
                    acitivity:(BOOL)bAcitve
                 autoHideTime:(NSTimeInterval)time
                          tag:(NSInteger)tag;

- (void)showDownloadProgressHudOnView:(UIView*)view 
                              caption:(NSString*)caption
                                image:(UIImage*)image
                            acitivity:(BOOL)bAcitve
                         autoHideTime:(NSTimeInterval)time;

- (void)updateProress:(CGFloat)progress forCation:(NSString*)caption;

// 隐藏hud
- (void)hideHud;
- (void)hideHudAfter:(NSTimeInterval)time;



@end
