//
//  SAPIHudHelper.m
//  RenrenSixin
//
//  Created by  on 12-2-24.
//  Copyright (c) 2012年 renren. All rights reserved.
//

#import "SAPIHudHelper.h"
#import <UIKit/UIApplication.h>
#import "UIView+UIViewExt.h"

static SAPIHudHelper* instance = nil;

static const CGFloat kProgressMin = 0.01f;

@interface SAPIHudHelper(Private)

- (void)setHudCaption:(NSString*)caption image:(UIImage*)image acitivity:(BOOL)bAcitve;
- (void)showHudAutoHideAfter:(NSTimeInterval)time;

- (void)hideHudTime:(NSString*)obj;

@end

@interface SAPIHudHelper()
@property (nonatomic, retain) id target;
@property (nonatomic, assign) SEL actionCallBack;
@property (nonatomic, retain) NSString* showingCaption;
//@property (nonatomic, assign) NSInteger tag;
@end

@implementation SAPIHudHelper


@synthesize hud = _hud;
@synthesize showingCaption = _showingCaption;

@synthesize target= _target;
@synthesize actionCallBack = _actionCallBack;
//@synthesize tag = _tag;

+ (SAPIHudHelper*) getInstance
{
    @synchronized(self){
        if (!instance) {
            instance = [[SAPIHudHelper alloc] init];
        }
        return instance;
    }
}

- (id) init
{
    self = [super init];
    return self;
}

- (void)dealloc
{
    self.target = nil;
    self.actionCallBack = nil;
    
    [self hideHud];
}

#pragma mark - public method
// 在window上显示hud
- (void)showHudOnWindow:(NSString*)caption 
                  image:(UIImage*)image
              acitivity:(BOOL)bAcitve
           autoHideTime:(NSTimeInterval)time
{
    [self setHudCaption:caption image:image acitivity:bAcitve];
    [self.hud setAccessoryPosition:ATMHudAccessoryPositionTop];
    
//    UIApplicationDelegate app = [UIApplication sharedApplication].delegate;
    [[UIApplication sharedApplication].delegate.window addSubview:self.hud.view];
    
    [self showHudAutoHideAfter:time];
}

// 在当前的view上显示hud
- (void)showHudOnView:(UIView*)view 
              caption:(NSString*)caption
                image:(UIImage*)image
            acitivity:(BOOL)bAcitve
         autoHideTime:(NSTimeInterval)time
{
    [self setHudCaption:caption image:image acitivity:bAcitve];
    [self.hud setAccessoryPosition:ATMHudAccessoryPositionTop];  
    
    [view addSubview:self.hud.view];
    
    [self showHudAutoHideAfter:time];
}


- (void)showHudOnView:(UIView*)view
              caption:(NSString*)caption
                image:(UIImage*)image
            acitivity:(BOOL)bAcitve
         autoHideTime:(NSTimeInterval)time
               target:(id)aTarget
             selector:(SEL)aSelector
{
    [self setHudCaption:caption image:image acitivity:bAcitve];
    [self.hud setAccessoryPosition:ATMHudAccessoryPositionTop];
    
    [view addSubview:self.hud.view];
    self.target = aTarget;
    self.actionCallBack = aSelector;
    
    [self showHudAutoHideAfter:time];
}

- (void)showProgressHudOnView:(UIView*)view 
                      caption:(NSString*)caption
                        image:(UIImage*)image
                    acitivity:(BOOL)bAcitve
                 autoHideTime:(NSTimeInterval)time
{
    [self setHudCaption:caption image:image acitivity:bAcitve];
    [self.hud setAccessoryPosition:ATMHudAccessoryPositionTop];  
    [view addSubview:self.hud.view];
    [self.hud setProgress:kProgressMin];
    [self showHudAutoHideAfter:time];
}

- (void)showDownloadProgressHudOnView:(UIView*)view
                      caption:(NSString*)caption
                        image:(UIImage*)image
                    acitivity:(BOOL)bAcitve
                 autoHideTime:(NSTimeInterval)time
                          tag:(NSInteger)tag
{
    [self showDownloadProgressHudOnView:view
                                caption:caption
                                  image:image
                              acitivity:bAcitve
                           autoHideTime:time];
}

- (void)showDownloadProgressHudOnView:(UIView*)view 
                      caption:(NSString*)caption
                        image:(UIImage*)image
                    acitivity:(BOOL)bAcitve
                 autoHideTime:(NSTimeInterval)time
{
    [self setHudCaption:caption image:image acitivity:bAcitve];
    [self.hud setAccessoryPosition:ATMHudAccessoryPositionBottom];  
    [view addSubview:self.hud.view];
    [self.hud setProgress:kProgressMin];
    [self showHudAutoHideAfter:time];

}

- (void)updateProress:(CGFloat)progress forCation:(NSString*)caption
{
    if (self.hud != nil) {
        if (progress < kProgressMin) {
            progress = kProgressMin;
        }
        [self.hud setActivity:NO];
        [self.hud setCaption:caption];
        [self.hud setProgress:progress];
        [self.hud update];
    }
}

- (void)enableSuperViewInteraction:(BOOL)enable
{
    self.hud.allowSuperviewInteraction = enable;
}

// 隐藏hud
- (void)hideHud
{
    self.showingCaption = nil;
    if(self.hud != nil)
    {
        [self.hud setProgress:0.0f];
        [self.hud.view removeFromSuperview];
        [self.hud hide];
        self.hud = nil;
    }
    if (self.target != nil && self.actionCallBack != nil) {
        if ([self.target respondsToSelector:self.actionCallBack] == YES) {
#pragma clang diagnostic ignored "-Warc-performSelector-leaks"
            [self.target performSelector:self.actionCallBack];
        }
        
    }
    self.target = nil;
    self.actionCallBack = nil;
}

- (void)hideHudTime:(NSString*)obj
{
    if (self.showingCaption != nil && [self.showingCaption isEqualToString:obj]) {
        [self hideHud];
    }
}

- (void)hideHudAfter:(NSTimeInterval)time
{
    NSString* obj = [self.showingCaption copy];
	[self performSelector:@selector(hideHudTime:) withObject:obj afterDelay:time];
}

#pragma mark - private method

- (void)setHudCaption:(NSString*)caption image:(UIImage*)image acitivity:(BOOL)bAcitve
{
    // 强制清除一下
    [self hideHud];
    self.showingCaption = caption;
    self.hud = [[ATMHud alloc] initWithDelegate:nil];
    if (image != nil) {
        [self.hud setImage:image];
    }
    
    [self.hud setCaption:caption];
    
    if (bAcitve) {
        [self.hud setActivity:YES];
        [self.hud setActivityStyle:UIActivityIndicatorViewStyleWhiteLarge];
    } else {
        [self.hud setActivity:NO];
    }
}

- (void)showHudAutoHideAfter:(NSTimeInterval)time
{
    [self.hud show];
    
    if (time > 0.0f) {
        [self hideHudAfter:time];
    }
}


@end
