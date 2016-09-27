//
//  SideLayer.hpp
//  AimSSB
//
//  Created by Machintosh on 27/09/16.
//
//

#ifndef SideLayer_hpp
#define SideLayer_hpp

#include <stdio.h>
#include "cocos2d.h"
#include "ui/CocosGUI.h"
#include "ui/UIWidget.h"
#include "extensions/cocos-ext.h"
#include "ui/UIPageView.h"

using namespace cocos2d::ui;
USING_NS_CC;


class SideLayer : public cocos2d::Layer
{
    
    cocos2d::Size visibleSize;
    
    cocos2d::EventListenerTouchOneByOne *listener;
    cocos2d::EventListenerKeyboard *m_keyboardListener;
    LayerColor* m_backgroundLayer;
    LayerColor* m_contentLayer;
    
    virtual bool init();
    virtual void onEnter();
    virtual void onExit();
    
public:
    // there's no 'id' in cpp, so we recommend returning the class instance pointer
    static SideLayer* createLayer();
    
    
    void createBackground();
    void createContentLayer();
    void runEnterAnimation();
    void runExitAnimation();
    
    
    CREATE_FUNC(SideLayer);
    
    virtual void onKeyReleased(EventKeyboard::KeyCode keyCode, Event *pEvent);
};

#endif /* SideLayer_hpp */
