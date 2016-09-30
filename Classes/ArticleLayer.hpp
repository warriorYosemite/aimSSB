//
//  ArticleLayer.hpp
//  AimSSB
//
//  Created by Machintosh on 30/09/16.
//
//

#ifndef ArticleLayer_hpp
#define ArticleLayer_hpp

#include <stdio.h>
#include "cocos2d.h"
#include "ui/CocosGUI.h"
#include "ui/UIWidget.h"
#include "extensions/cocos-ext.h"
#include "ui/UIPageView.h"
#include "commonClasses.h"
#include "ui/UIScrollView.h"

using namespace cocos2d::ui;
USING_NS_CC;

class ArticleLayer : public cocos2d::Layer//, public ScrollView, public cocos2d::extension::ScrollViewDelegate
{
    
    cocos2d::Size visibleSize;
    
    cocos2d::EventListenerTouchOneByOne *listener;
    cocos2d::EventListenerKeyboard *m_keyboardListener;
   
    LayerColor* m_backgroundLayer;
    LayerColor* m_contentLayer;
    
    ScrollView* m_scrollView;
    
    std::vector<ItemsDetailStruct*> m_contentList;

    
    virtual bool init();
    virtual void onEnter();
    virtual void onExit();
    
public:
    // there's no 'id' in cpp, so we recommend returning the class instance pointer
    static ArticleLayer* createLayer();
    
    
    void createBackground();
    void createScrollView();
    
    
    CREATE_FUNC(ArticleLayer);
    
    virtual void onKeyReleased(EventKeyboard::KeyCode keyCode, Event *pEvent) override;
    
//    virtual void scrollViewDidScroll(ScrollView* view) override;
//    virtual void scrollViewDidZoom(ScrollView* view)  override {}
    
//    virtual bool onTouchBegan(Touch *pTouch, Event *pEvent) override;
//    virtual void onTouchMoved(Touch *pTouch, Event *pEvent) override;
//    virtual void onTouchEnded(Touch *pTouch, Event *pEvent) override;
//    virtual void onTouchCancelled(Touch *pTouch, Event *pEvent) override;
    
};




#endif /* ArticleLayer_hpp */
