//
//  TMLazyScrollView.h
//  LazyScrollView
//
//  Copyright (c) 2015-2018 Alibaba. All rights reserved.
//

#import <UIKit/UIKit.h>
#import "TMLazyItemViewProtocol.h"
#import "TMLazyRectModel.h"

@class TMLazyScrollView;


/**
 A UIView category required by LazyScrollView.
 */
@interface UIView (TMLazyScrollView)

// A uniq string that identify a view, require to
// be same as muiID of the model.
@property (nonatomic, copy, nullable) NSString *muiID;
// A string used to identify a view that is reusable.
@property (nonatomic, copy, nullable) NSString *reuseIdentifier;

- (nonnull instancetype)initWithFrame:(CGRect)frame
                      reuseIdentifier:(nullable NSString *)reuseIdentifier;

@end

//****************************************************************

/**
 This protocol represents the data model object.
 */
@protocol TMLazyScrollViewDataSource <NSObject>

@required

// 0 by default.
- (NSUInteger)numberOfItemInScrollView:(nonnull TMLazyScrollView *)scrollView;
// Return the view model by spcial index.
- (nonnull TMLazyRectModel *)scrollView:(nonnull TMLazyScrollView *)scrollView
                      rectModelAtIndex:(NSUInteger)index;
// You should render the item view here.
// You should ALWAYS try to reuse views by setting each view's reuseIdentifier.
- (nonnull UIView *)scrollView:(nonnull TMLazyScrollView *)scrollView
                   itemByMuiID:(nonnull NSString *)muiID;

@end
//****************************************************************


@interface TMLazyScrollView : UIScrollView

// 注意，修改 delegate 属性后需要将 scrollViewDidScroll: 事件转发回给 TangramView

@property (nonatomic, weak, nullable) id<TMLazyScrollViewDataSource> dataSource;

@property (nonatomic, weak, nullable) id<UIScrollViewDelegate> forwardingDelegate;

// Default value is NO.
@property (nonatomic, assign) BOOL autoAddSubview;

// Items which has been added to LazyScrollView.
@property (nonatomic, strong, readonly, nonnull) NSSet<UIView *> *visibleItems;
// Items which is in the visible screen area.
// It is a sub set of "visibleItems".
@property (nonatomic, strong, readonly, nonnull) NSSet<UIView *> *inScreenVisibleItems;
// Tangram can be footerView for TableView, this outerScrollView is your tableview.
@property (nonatomic, weak, nullable) UIScrollView *outerScrollView;


// reloads everything from scratch and redisplays visible views.
- (void)reloadData;
// Remove all subviews and reuseable views.
- (void)removeAllLayouts;

// Get reuseable view by reuseIdentifier. If cannot find reuseable
// view by reuseIdentifier, here will return nil.
- (nullable UIView *)dequeueReusableItemWithIdentifier:(nonnull NSString *)identifier;
// Get reuseable view by reuseIdentifier and muiID.
// MuiID has higher priority.
- (nullable UIView *)dequeueReusableItemWithIdentifier:(nonnull NSString *)identifier
                                                 muiID:(nullable NSString *)muiID;

// After call this method, the times of mui_didEnterWithTimes will start from 0
- (void)resetViewEnterTimes;

@end

//****************************************************************

@interface TMLazyScrollViewObserver: NSObject
@property (nonatomic, weak, nullable) TMLazyScrollView *lazyScrollView;
@end