//
//  LoginViewController.swift
//  testsapi
//
//  Created by zhaoxiaolu on 15/6/11.
//  Copyright (c) 2015年 zhaoxiaolu. All rights reserved.
//

import UIKit

class LoginViewController: UIViewController, SAPIMainWebViewDelegate {
    
    var navBar:UINavigationBar!
    
    var _notFoundImgView:UIImageView!
    
    var notFoundImgView:UIImageView! {
        get {
            if _notFoundImgView == nil {
                var notFoundImg:UIImage = UIImage(named: "sapi_404")!
                var x:CGFloat = (self.view.frame.size.width - notFoundImg.size.width) / 2
                var y:CGFloat = (self.view.frame.size.height - notFoundImg.size.height) / 2
                var frame:CGRect = CGRectMake(x, y, notFoundImg.size.width, notFoundImg.size.height)
                _notFoundImgView = UIImageView(frame: frame)
                _notFoundImgView.image = notFoundImg
                _notFoundImgView.hidden = true
            }
            return _notFoundImgView
        }
    }
    
    var upOffset:CGFloat!
    
//    var registerPlugin:SAPIRegisterService!
    
    var _mainWebView:SAPIMainWebView!
    
    var mainWebView:SAPIMainWebView! {
        get {
            if self._mainWebView == nil {
                _mainWebView = SAPIMainWebView(frame: CGRectMake(0, 0, self.view.frame.size.width, self.view.frame.size.height))
                _mainWebView.mainWebViewDelegate = self
            }
            return self._mainWebView
        }
    }

    override func viewDidLoad() {
        super.viewDidLoad()
        self.initView()
        self.goToLogin()
        // Do any additional setup after loading the view.
    }

    override func didReceiveMemoryWarning() {
        super.didReceiveMemoryWarning()
        // Dispose of any resources that can be recreated.
    }
    
    func initView() {
        self.view.backgroundColor = UIColor.whiteColor()
        self.view.addSubview(self.mainWebView)
        // 兼容配置
        self.configuration()
        // 插件配置
        self.initPlugins()
        self.view.insertSubview(self.notFoundImgView, belowSubview: self.mainWebView)
        self.createNavBar()
    }
    
    func configuration() {
        self.upOffset = 0.0
        
        //ios7及以后的版本
        var iosVersionCompare = UIDevice.currentDevice().systemVersion.caseInsensitiveCompare("7.0.0")
        if (iosVersionCompare == NSComparisonResult.OrderedSame || iosVersionCompare == NSComparisonResult.OrderedDescending) {
            self.upOffset = 20.0
            var compatibilityBar:UIView = UIView(frame: CGRectMake(0, 0, self.view.frame.size.width, 21.0))
            compatibilityBar.backgroundColor = UIColor(red: 247/255, green: 247/255, blue: 247/255, alpha: 1.0)
            self.view.addSubview(compatibilityBar)
        }
        var frame:CGRect = self.mainWebView.frame
        frame.origin.y += self.upOffset
        self.mainWebView.frame = frame
        
        for subview in self.mainWebView.subviews {
            if subview.isKindOfClass(UIScrollView) {
                var a:UIScrollView = subview as! UIScrollView
                a.bounces = false
//                UIScrollView(coder: subview as! NSCoder).bounces = false
            }
        }
    }
    
    func initPlugins() {
        // 控制插件
        var controlPlugin:SAPIControlPlugin = SAPIControlPlugin()
        controlPlugin.webViewController = self
        self.mainWebView.addPlugin(controlPlugin)
        
        // 注册插件
//        self.registerPlugin = SAPIControlPlugin()
//        self
        
        // 同步页面缓存
        SAPIMainManager.sharedManager().syncCacheOnCompletion({ () -> Void in
            NSLog("sync cache success")
        }, error: { () -> Void in
            NSLog("sync cache fail")
        })
        
        // Oauth 强制登录
        SAPIMainManager.sharedManager().isOauthForceLogin = false
        
        // 是否显示新样式
        SAPIMainManager.sharedManager().showIPlayout = true
        
        // 第三方登录 暗绑
        SAPIMainManager.sharedManager().shareBindMode = SAPIShareImplicitBindMode
        
        // 先清除之前的快捷选项
        SAPIMainManager.sharedManager().clearLoginOptions()
        
        // 导航插件
        var navPlugin:SAPINavPlugin = SAPINavPlugin()
        navPlugin.webViewController = self
        self.mainWebView.addPlugin(navPlugin)
        
    }
    
    func createNavBar() {
        self.navBar = UINavigationBar(frame: CGRectMake(0, 0, self.view.bounds.width, 44))
//        var imagView = UIImageView()
        self.navBar.backgroundColor = UIColor.blackColor()
        self.view.addSubview(self.navBar)
        
        var NavTitle:UINavigationItem = UINavigationItem(title: "登录")
        self.navBar.pushNavigationItem(NavTitle, animated: true)
        
        var backBtn:UIButton = UIButton(frame: CGRectMake(10, 10, 50, 29))
        backBtn.backgroundColor = UIColor.clearColor()
        backBtn.setTitleColor(UIColor.whiteColor(), forState: UIControlState.Normal)
        backBtn.setTitle("返回", forState: UIControlState.Normal)
        backBtn.titleEdgeInsets = UIEdgeInsetsMake(0, 5, 0, 0)
        backBtn.titleLabel?.font = UIFont.systemFontOfSize(13)
        backBtn.addTarget(self, action: "goBack:", forControlEvents: UIControlEvents.TouchUpInside)
        var backBarBtn = UIBarButtonItem(customView: backBtn)
        self.navBar.topItem?.leftBarButtonItem = backBarBtn
        self.navBar.hidden = true
    }
    
    func refresh() {
        self.goToLogin()
    }
    
    func goBack(sender:UIButton) {
        if !self.mainWebView.viewLoaded {
            self.navigationController?.popViewControllerAnimated(true)
            return
        }
        self.cancelAllRequest()
        if !self.mainWebView.historyBack() {
            self.navigationController?.popViewControllerAnimated(true)
        }
        
    }
    
    func goToLogin() {
        println(SAPIMainManager.sharedManager().mainLoginUrl)
        self.mainWebView.load(SAPIMainManager.sharedManager().mainLoginUrl)
    }
    
    func cancelAllRequest() {
        self.mainWebView.cancelAllRequest()
//        self.registerPlugin.cancelAllRequest()
    }
    
    //pragma mark private methods
    func showNotFoundView() {
        self.notFoundImgView.hidden = false
        self.mainWebView.hidden = true
        self.showNavBar()
    }
    
    func hideNotFoundView() {
        self.notFoundImgView.hidden = true
        self.mainWebView.hidden = false
        self.hideNavBar()
    }
    
    func showNavBar() {
        self.navBar.hidden = false
        var y:CGFloat = self.upOffset + self.navBar.bounds.size.height
        self.mainWebView.frame = CGRectMake(0, y, self.view.frame.size.width, self.view.frame.size.height - y)
    }
    
    func hideNavBar() {
        var y:CGFloat = self.upOffset
        self.mainWebView.frame = CGRectMake(0, y, self.view.frame.size.width, self.view.frame.size.height - y)
        self.navBar.hidden = true
    }
    
    //pragma mark - mainWebViewControllerDelegate
    func sapiWebView(webView: SAPIWebView!, mainViewShouldStartLoadWithRequest request: NSURLRequest!, navigationType: UIWebViewNavigationType) -> Bool {
        if request.URL?.scheme == "sms" {
            UIApplication.sharedApplication().openURL(request.URL!)
            return false
        }
        return true
    }
    
    func sapiWebViewDidStartLoadFromNetwork(webView: SAPIWebView!) {
        self.hideNotFoundView()
        println("hide hud")
    }
    
    func sapiWebViewDidStartLoadFromCache(webView: SAPIWebView!) {
        println("hide hud1")
    }
    
    func sapiWebViewDidFinishLoadFromNetwork(webView: SAPIWebView!) {
        println("hide hud2")
        self.sapiWebViewLoadFinished(webView)
    }
    
    func sapiWebViewDidFinishLoadFromCache(webView: SAPIWebView!) {
        self.sapiWebViewLoadFinished(webView)
    }
    
    func sapiWebView(webView: SAPIWebView!, didFailLoadFromNetWorkWithError error: NSError!) {
        self.showNotFoundView()
        println("hide hud3")
    }
    
    func sapiWebView(webView: SAPIWebView!, didFailLoadFromCacheWithError error: NSError!) {
        self.showNotFoundView()
    }
    
    func sapiWebViewLoadFinished(webView:SAPIWebView) {
        var currentURL:NSURL? = webView.currentURL()
        if (currentURL != nil) {
            if self.mainWebView.checkInWhiteList(currentURL) {
                self.showNavBar()
                var title:NSString = self.mainWebView.titleForWhiteListURL(currentURL)
            } else {
                self.hideNavBar()
            }
        } else {
            self.hideNavBar()
        }
    }

}
