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
#include "commonClasses.h"

using namespace cocos2d::ui;
USING_NS_CC;


class SideLayer : public cocos2d::Layer,public cocos2d::extension::TableViewDataSource, public cocos2d::extension::TableViewDelegate
{
    
    cocos2d::Size visibleSize;
    
    cocos2d::EventListenerTouchOneByOne *listener;
    cocos2d::EventListenerKeyboard *m_keyboardListener;
    LayerColor* m_backgroundLayer;
    LayerColor* m_contentLayer;
    LayerColor* quoteLayer;
    
    int m_tableSize;
    float tableWidth;
    float tableHeight;
    float rowHeight;
    
    cocos2d::extension::TableView* m_tableView;
    std::vector<ItemsDetailStruct*> m_contentList;
    
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
    void setDataList();
    
    void createTableView();
    
    CREATE_FUNC(SideLayer);
    
    virtual void onKeyReleased(EventKeyboard::KeyCode keyCode, Event *pEvent);
    
    virtual void tableCellTouched(cocos2d::extension::TableView* table, cocos2d::extension::TableViewCell* cell);
    virtual cocos2d::Size tableCellSizeForIndex(cocos2d::extension::TableView *table, ssize_t idx);
    virtual cocos2d::extension::TableViewCell* tableCellAtIndex(cocos2d::extension::TableView *table, ssize_t idx);
    virtual ssize_t numberOfCellsInTableView(cocos2d::extension::TableView *table);
};

#endif /* SideLayer_hpp */
