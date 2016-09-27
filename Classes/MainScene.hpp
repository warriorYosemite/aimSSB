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
    cocos2d::ui::PageView* m_pageView;
    
    int m_numOfPages;
    bool isReverse;
    
    void createBackground();
    void createPageView();
    void updatePages(float dt);
    
    void pageViewEvent(cocos2d::Ref *sender , cocos2d::ui::PageView::EventType type );
    void appendCubicBezier(int startPoint, std::vector<Vec2>& verts, const Vec2& from, const Vec2& control1, const Vec2& control2, const Vec2& to, uint32_t segments);
    Node* createRoundedRectMaskNode(Size size, float radius, float borderWidth, int cornerSegments);
    
    
    
    void listItemCallback(Ref* pSender);
    void shareItemCallBack(Ref* pSender);
    
    CREATE_FUNC(MainScene);
    
    virtual void onKeyReleased(EventKeyboard::KeyCode keyCode, Event *pEvent);
};

#endif /* MainScene_hpp */
