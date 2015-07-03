//: Playground - noun: a place where people can play

import UIKit

var str = "Hello, playground"
var ids:NSArray = [1,2,3,4,5,3]
var id:Int = 3
let pre:NSPredicate = NSPredicate(format: "self == %@", NSNumber(integer: id))
let a = ids.filteredArrayUsingPredicate(pre)
var b = a.count


