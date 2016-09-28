//  Created by Kuldeep Teekas
//  Dated : 8-09-2015
//

#ifndef __CONTENT_LAYER_H__
#define __CONTENT_LAYER_H__

#include "cocos2d.h"
#include "ui/CocosGUI.h"
#include "constant.h"
#include "ui/UIWidget.h"
#include <exception>
#include "extensions/cocos-ext.h"
#include "CocosGUI.h"
#include "commonClasses.h"

using namespace cocos2d::ui;
USING_NS_CC;


class ContentLayer : public cocos2d::Layer,public cocos2d::extension::TableViewDataSource, public cocos2d::extension::TableViewDelegate
{

public:
    
    cocos2d::Size visibleSize;
    
    static ContentLayer* createLayer(float width, float height);

    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();
    
    int m_tableSize;
    float tableWidth;
    float tableHeight;
    float rowHeight;

    CONTENT_TYPE m_contentType;
    
    cocos2d::extension::TableView* m_tableView;
    std::vector<ItemsDetailStruct*> m_contentList;
    
    // a selector callback
    void menuCloseCallback(cocos2d::Ref* pSender);
    cocos2d::EventListenerTouchOneByOne *listener;
    
    
    void createBackground();
    void createTableView();
    void setContentType(CONTENT_TYPE contentType);
    void setContentList(std::vector<ItemsDetailStruct*> contentList, bool isReload);
    
    virtual void onEnter();
    virtual void onExit();
    
    // implement the "static create()" method manually
    CREATE_FUNC(ContentLayer);
    
    virtual void tableCellTouched(cocos2d::extension::TableView* table, cocos2d::extension::TableViewCell* cell);
    virtual cocos2d::Size tableCellSizeForIndex(cocos2d::extension::TableView *table, ssize_t idx);
    virtual cocos2d::extension::TableViewCell* tableCellAtIndex(cocos2d::extension::TableView *table, ssize_t idx);
    virtual ssize_t numberOfCellsInTableView(cocos2d::extension::TableView *table);
   

};

#endif // __CONTENT_LAYER_H__
