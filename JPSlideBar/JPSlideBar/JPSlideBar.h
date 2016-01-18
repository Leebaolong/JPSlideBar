//
//  JPSlideBar.h
//  JPSlideBar
//
//  QQ:844 840 850
//
//  Created by apple on 15/12/30.
//  Copyright © 2015年 XiFengLang. All rights reserved.
//

#import <UIKit/UIKit.h>
#import "UIColor+JPExtension.h"


#define JColor_RGB_Float(R,G,B)   ([UIColor colorWithRed:(R) green:(G) blue:(B) alpha:1])
#define JColor_RGB(R,G,B)         ([UIColor colorWithRed:(R)/255.0 green:(G)/255.0 blue:(B)/255.0 alpha:1.0])


#define JPSLIDER_ITEM_SPACE 20.0
#define JPSLIDER_HEIGHT  42.0
#define JPSCREEN_WIDTH  [UIScreen mainScreen].bounds.size.width
#define JPSCREEN_HEIGHT [UIScreen mainScreen].bounds.size.height
#define JPSLIDER_FONT   [UIFont systemFontOfSize:18]


#define JPNotificationCenter [NSNotificationCenter defaultCenter]
#define JPScrollViewDidChangePageNotification  @"didChangePageNotification"
#define JPScrollViewContentOffsetX  @"contentOffsetX"
#define JPSlideBarCurrentIndex      @"currentIndex"


#ifdef  DEBUG
#define JKLog(...) NSLog(__VA_ARGS__)
#else
#define JKLog(...)
#endif


// 转弱转换的宏，主要用于Self强弱转换，不支持点语法
#ifndef    Weak
#if __has_feature(objc_arc)
#define Weak(object) __weak __typeof__(object) weak##object = object;
#else
#define Weak(object) autoreleasepool{} __block __typeof__(object) block##object = object;
#endif
#endif
#ifndef    Strong
#if __has_feature(objc_arc)
#define Strong(object) __typeof__(object) object = weak##object;
#else
#define Strong(object) try{} @finally{} __typeof__(object) object = block##object;
#endif
#endif




typedef void(^JPSlideBarSelectedBlock) (NSInteger index);

/**
 *  是否隐藏滑动条
 */
typedef NS_ENUM(NSInteger, JPSlideBarStyle) {
    /**
     *  仅改变字体颜色,隐藏滚动条
     */
    JPSlideBarStyleChangeColorOnly = 0,
    /**
     *  仅渐变颜色效果，隐藏滚动条
     */
    JPSlideBarStyleGradientColorOnly = 1,
    /**
     *  滚动条+改变字体颜色
     */
    JPSlideBarStyleShowSliderAndChangeColor = 2,
    /**
     *  滚动条+字体颜色渐变效果
     */
    JPSlideBarStyleShowSliderAndGradientColor = 3,
    /**
     *  大小渐变+颜色渐变(下一版本)
     */
    //JPSlideBarStyleTransformationAndGradientColor = 4
};



@interface JPSlideBar : UIVisualEffectView <UIScrollViewDelegate>
// 内部转换被监听scrollView的delegate，相当于self.delegate = scrollView.delegate ,scrollView.delegate = self
@property (nonatomic, weak, readonly) id<UIScrollViewDelegate> delegate;





/**
 *  初始化及显示JPSlideBar容器视图，titleArray.count <= 5时等宽处理，大于5个才支持形变。默认使用磨砂效果，设置背景颜色即可覆盖
 *
 *  @param viewController            内部实现[viewController.view addSubview:slideBar];
 *  @param frameOriginY              Y坐标
 *  @param space                     Item间隔，默认最小20
 *  @param slideBarStyle             JPSlideBar样式
 *
 */
+ (instancetype)showInViewController:(UIViewController *)viewController
                observableScrollView:(UIScrollView *)scrollView
                        frameOriginY:(CGFloat)frameOriginY
                           itemSpace:(CGFloat)space
                 slideBarSliderStyle:(JPSlideBarStyle)slideBarStyle;


/**
 *  配置JPSlideBar及完全显示
 *
 *  @param titleArray    title数组，count<=5时会做等宽处理，铺满屏幕
 *  @param font          正常状态下的字体（不再支持更改字体）
 *  @param normalColor   正常状态下的颜色
 *  @param selectedColor 选中后的字体、滑动条颜色
 *  @param selectedBlock 选择后的回调Block
 */
- (void)configureSlideBarWithTitles:(NSArray *)titleArray
                          titleFont:(UIFont  *)font
                normalTitleRGBColor:(UIColor *)normalColor
              selectedTitleRGBColor:(UIColor *)selectedColor
                      selectedBlock:(JPSlideBarSelectedBlock)selectedBlock;


///**   新版不再支持外部调用这个方法
// *  observableScrollView为nil时，在ScrollViewDidScroll代理方法中调用
// *
// *  @param offsetX scrollView的偏移量
// */
//- (void)updateSlideBarWhenScrollViewDidScrollWithOffsetX:(CGFloat)offsetX;


/**
 *  设置背景颜色,默认使用磨砂效果、半透明，设置背景颜色后可覆盖
 */
- (void)setSlideBarBackgroudColorIfNecessary:(UIColor *)color;


- (NSInteger)indexOfSlideBarItemDidSelected;

@end
