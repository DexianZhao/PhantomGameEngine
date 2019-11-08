//
//  ViewController.h
//  PhantomIOSSDK
//
//  Created by ZhaoDexian on 12-7-25.
//  Copyright (c) 2012年 __MyCompanyName__. All rights reserved.
//

#import <UIKit/UIKit.h>
#import <GLKit/GLKit.h>
#import <iAd/iAd.h>
#import "MyStoreKit.h"
//#import "DuoMobImpWall.h"

@interface ViewController : GLKViewController
{
    ADBannerView*   m_adView;
    MyStoreKit*     m_store;
    UITouch*        m_touchs[8];
//    DuoMobImpWall   *m_dwall;
}
+ (ViewController*)instance;
- (id)initWithB:(NSString *)nibNameOrNil bundle:(NSBundle *)nibBundleOrNil;
- (void) myLoadView;
- (void) gotoBuy:(NSString*)ids;
- (void) showWall;
- (void) hideAd;

@end
