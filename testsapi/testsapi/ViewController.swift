//
//  ViewController.swift
//  testsapi
//
//  Created by zhaoxiaolu on 15/6/11.
//  Copyright (c) 2015年 zhaoxiaolu. All rights reserved.
//

import UIKit

class ViewController: UIViewController {

    override func viewDidLoad() {
        super.viewDidLoad()
//        var ids:NSArray = [1,2,3,4,5]
//        let pre:NSPredicate = NSPredicate(format: "self == %@", NSNumber(int: 3))
//        var a = ids.filteredArrayUsingPredicate(pre)

//        println(a)
        self.view.backgroundColor = UIColor.whiteColor()
        var bt:UIButton = UIButton(frame: CGRectMake(100, 100, 100, 50))
        bt.setTitle("login", forState: UIControlState.Normal)
        bt.setTitleColor(UIColor.blackColor(), forState: UIControlState.Normal)
        bt.addTarget(self, action: "login:", forControlEvents: UIControlEvents.TouchUpInside)
        self.view.addSubview(bt)
        // Do any additional setup after loading the view, typically from a nib.
    }
    
    func login(sender:UIButton) {
        SAPIMainManager.sharedManager().showQuickLogin = false
        var loginWebViewController:LoginViewController = LoginViewController()
        loginWebViewController.title = "SAPI Login"
        self.presentViewController(loginWebViewController, animated: true, completion: nil)
    }

    override func didReceiveMemoryWarning() {
        super.didReceiveMemoryWarning()
        // Dispose of any resources that can be recreated.
    }


}

