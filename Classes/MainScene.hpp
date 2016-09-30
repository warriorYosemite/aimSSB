//
//  MainScene.hpp
//  AimSSB
//
//  Created by Machintosh on 27/09/16.
//
//

#ifndef MainScene_hpp
#define MainScene_hpp

#include <stdio.h>
#include "cocos2d.h"
#include "ui/CocosGUI.h"
#include "ui/UIWidget.h"
#include "extensions/cocos-ext.h"
#include "ui/UIPageView.h"
#include "SideLayer.hpp"
#include "commonClasses.h"
#include "ContentLayer.h"

using namespace cocos2d::ui;
USING_NS_CC;

class MainScene : public cocos2d::Layer
{

    cocos2d::Size visibleSize;
    
    cocos2d::EventListenerTouchOneByOne *listener;
    cocos2d::EventListenerKeyboard *m_keyboardListener;

public:
    // there's no 'id' in cpp, so we recommend returning the class instance pointer
   static cocos2d::Scene* createScene();
    
    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();
    virtual void onEnter();
    virtual void onExit();

    LayerColor* m_backgroundLayer;
    ContentLayer* contentLayerE;
    cocos2d::ui::PageView* m_pageView;
    cocos2d::Vector<cocos2d::MenuItem*> gameSelectionMenuItems;
    std::vector<ItemsDetailStruct*> m_latestItemsList;
    std::vector<ItemsDetailStruct*> m_notificationsItemsList;
    std::vector<ItemsDetailStruct*> m_ssbGuideItemsList;
    
    int m_numOfPages;
    bool isReverse;
    
    MenuItemSprite* latestPostItem;
    MenuItemSprite* ssbGuideItem;
    MenuItemSprite* notificationItem;
    
    
    void createBackground();
    void createPageView();
    void createMenuItems();
    void updatePages(float dt);
    void createContentHolder();
    
    void setDataLatestItem();
    void setDataNotificationItem();
    void setSSBGuideList();
    
    void pageViewEvent(cocos2d::Ref *sender , cocos2d::ui::PageView::EventType type );
    
    void listItemCallback(Ref* pSender);
    void shareItemCallBack(Ref* pSender);
    void latestPostCallBack(Ref* pSender);
    void ssbGuideCallBack(Ref* pSender);
    void notificationCallBack(Ref* pSender);
    
    CREATE_FUNC(MainScene);
    
    virtual void onKeyReleased(EventKeyboard::KeyCode keyCode, Event *pEvent);
};

#endif /* MainScene_hpp */
