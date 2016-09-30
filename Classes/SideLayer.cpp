//
//  SideLayer.cpp
//  AimSSB
//
//  Created by Machintosh on 27/09/16.
//
//

#include "SideLayer.hpp"
#include "constant.h"

using namespace cocos2d::extension;
using namespace std;

SideLayer* SideLayer::createLayer()
{
    
    // 'layer' is an autorelease object
    auto layer = SideLayer::create();
    
    
    // return the layer
    return layer;
}

// on "init" you need to initialize your instance
bool SideLayer::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }
    
    return true;
}

void SideLayer::onEnter()
{
    Layer::onEnter();
    m_keyboardListener = NULL;
    
    visibleSize = Director::getInstance()->getVisibleSize();
    
    auto dispatcher = Director::getInstance()->getEventDispatcher();
    listener = EventListenerTouchOneByOne::create();
    listener->onTouchBegan = [=](Touch* touch, Event* event){
        
        event->stopPropagation();
        
        auto target = static_cast<LayerColor*>(event->getCurrentTarget());
        Vec2 locationInNode = target->convertToNodeSpace(touch->getLocation());
        Vec2 locationInNodeBG;
        Size s;
        
        locationInNodeBG = m_contentLayer->convertToNodeSpace(touch->getLocation());
        s = m_contentLayer->getContentSize();
        Rect rect = Rect(0, 0, s.width, s.height);
        if (rect.containsPoint(locationInNodeBG))
        {
            log("sprite began... x = %f, y = %f", locationInNode.x, locationInNode.y);
            return true;
        }
        else
        {
            this->runExitAnimation();
        }
        return true;
    };
    
    listener->setSwallowTouches(true);
    dispatcher->addEventListenerWithSceneGraphPriority(listener, this);
    listener->retain();
    
    m_keyboardListener = EventListenerKeyboard::create();
    m_keyboardListener->onKeyReleased = CC_CALLBACK_2(SideLayer::onKeyReleased, this);
    Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(m_keyboardListener, this);
    
    setDataList();
    
    createBackground();
    createContentLayer();
    
    createTableView();
    
    runEnterAnimation();
}

void SideLayer::setDataList(){

    ItemsDetailStruct* item1 = new ItemsDetailStruct();
    item1->m_heading = "How to Join";
    item1->m_imageURL = ICON_PATH"icon1.png";
    m_contentList.push_back(item1);
    
    ItemsDetailStruct* item2 = new ItemsDetailStruct();
    item2->m_heading = "SSB Tips";
    item2->m_imageURL = ICON_PATH"icon2.png";
    m_contentList.push_back(item2);
    
    ItemsDetailStruct* item3 = new ItemsDetailStruct();
    item3->m_heading = "Share Your Story";
    item3->m_imageURL = ICON_PATH"icon3.png";
    m_contentList.push_back(item3);
    
    ItemsDetailStruct* item4 = new ItemsDetailStruct();
    item4->m_heading = "SSB Centres";
    item4->m_imageURL = ICON_PATH"icon4.png";
    m_contentList.push_back(item4);
    
    ItemsDetailStruct* item5 = new ItemsDetailStruct();
    item5->m_heading = "Achievers";
    item5->m_imageURL = ICON_PATH"icon5.png";
    m_contentList.push_back(item5);
    
    ItemsDetailStruct* item6 = new ItemsDetailStruct();
    item6->m_heading = "Rate Us";
    item6->m_imageURL = ICON_PATH"icon6.png";
    m_contentList.push_back(item6);
    
    ItemsDetailStruct* item7 = new ItemsDetailStruct();
    item7->m_heading = "Be A Writer";
    item7->m_imageURL = ICON_PATH"icon7.png";
    m_contentList.push_back(item7);
    
    ItemsDetailStruct* item8 = new ItemsDetailStruct();
    item8->m_heading = "Settings";
    item8->m_imageURL = ICON_PATH"icon8.png";
    m_contentList.push_back(item8);
    
    ItemsDetailStruct* item9 = new ItemsDetailStruct();
    item9->m_heading = "Feedback";
    item9->m_imageURL = ICON_PATH"icon9.png";
    m_contentList.push_back(item9);
    
    ItemsDetailStruct* item10 = new ItemsDetailStruct();
    item10->m_heading = "Help And Support";
    item10->m_imageURL = ICON_PATH"icon10.png";
    m_contentList.push_back(item10);
    
    ItemsDetailStruct* item11 = new ItemsDetailStruct();
    item11->m_heading = "About Us";
    item11->m_imageURL = ICON_PATH"icon11.png";
    m_contentList.push_back(item11);
    
}

void SideLayer::createTableView(){
    
    tableWidth = this->getContentSize().width;
    tableHeight = this->getContentSize().height - quoteLayer->getContentSize().height;
    
    
    m_tableView = cocos2d::extension::TableView::create(this, Size(tableWidth,tableHeight));
    m_tableView->setDirection(cocos2d::extension::TableView::Direction::VERTICAL);
    m_tableView->setPosition(Vec2(0,0));
    m_tableView->setDelegate(this);
    m_tableView->setVerticalFillOrder(cocos2d::extension::TableView::VerticalFillOrder::TOP_DOWN);
    m_contentLayer->addChild(m_tableView);
    
}

TableViewCell* SideLayer::tableCellAtIndex(TableView *table, ssize_t idx)
{
    TableViewCell *cell = table->dequeueCell();
    if (cell)
    {
        cell->removeAllChildrenWithCleanup(true);
    }
    else
    {
        cell = new TableViewCell();
        cell->autorelease();
        
    }
    
    std::string iconPath = m_contentList.at(idx)->m_imageURL;
    std::string name = m_contentList.at(idx)->m_heading;
    
    Sprite* icon = Sprite::create(iconPath);
    icon->setAnchorPoint(Vec2(0, 0.5));
    icon->setPosition(Vec2(20, rowHeight * 0.5));
    cell->addChild(icon);
    
    Label* nameLabel = Label::createWithTTF(name, FONT_DOSIS, 27);
    nameLabel->setAnchorPoint(Vec2(0, 0.5));
    nameLabel->setColor(Color3B::BLACK);
    nameLabel->setPosition(Vec2(tableWidth * 0.15, rowHeight * 0.5));
    cell->addChild(nameLabel);
    
    return cell;
}

Size SideLayer::tableCellSizeForIndex(cocos2d::extension::TableView *table, ssize_t idx)
{
    rowHeight = 100;
    return Size(tableWidth, rowHeight);
}

void SideLayer::tableCellTouched(TableView *table, TableViewCell *cell)
{
    
    CCLOG("CELL %zd ", cell->getIdx());
    
    int idx = (int)cell->getIdx();
    
}

ssize_t SideLayer::numberOfCellsInTableView(TableView *table)
{
    int size = (int)m_contentList.size();
    return size;
}

void SideLayer::runEnterAnimation()
{
    
    CCLOG("into enter animation");
    
    CallFunc* callFun1 = CallFunc::create([=] {
        
        
    });
    
    MoveTo* enterAnimation =  MoveTo::create(0.3, Vec2(0,0));
    auto animationSeq = Sequence::create(callFun1, enterAnimation,NULL);
    m_backgroundLayer->runAction(animationSeq);
}

void SideLayer::runExitAnimation(){
    
    CCLOG("into exit animation");
    
    CallFunc* callFun1 = CallFunc::create([=] {
        
        this->removeFromParentAndCleanup(true);
    });
    
    CallFunc* callFun2 = CallFunc::create([=]{
        
//        GamePlay::getInstance()->setStatusBettingPanelButton(true);
    });
    
    MoveTo* exitAnimation =  MoveTo::create(0.3, Vec2(-visibleSize.width,0));
    auto exitAnimationSeq = Sequence::create(exitAnimation,callFun1,callFun2,  NULL);
    m_backgroundLayer->runAction(exitAnimationSeq);
    
}


void SideLayer::createBackground(){
    
    m_backgroundLayer = LayerColor::create(Color4B::Color4B(0,0,0,180), visibleSize.width, visibleSize.height);
    m_backgroundLayer->setPosition(Vec2(-visibleSize.width,0));
    this->addChild(m_backgroundLayer);
    
}

void SideLayer::createContentLayer(){

    m_contentLayer = LayerColor::create(Color4B::WHITE, visibleSize.width * 0.75, visibleSize.height);
    m_contentLayer->setPosition(Vec2(0, 0));
    m_backgroundLayer->addChild(m_contentLayer);
    
    quoteLayer = LayerColor::create(Color4B(51,64,28,255), m_contentLayer->getContentSize().width, m_contentLayer->getContentSize().height * 0.15);
    quoteLayer->setPosition(Vec2(0, m_contentLayer->getContentSize().height - quoteLayer->getContentSize().height));
    m_contentLayer->addChild(quoteLayer);
    
    std::string message = " 'If a man says he is not afraid of dying,\nhe is either lying or is a Gurkha.' \n\n -Field Marshal Sam Manekshaw";
    Label* quoteOfTheDay = Label::createWithTTF(message, FONT_SOURCE_SANS, 22);
    quoteOfTheDay->setAlignment(cocos2d::TextHAlignment::CENTER);
    quoteOfTheDay->setAnchorPoint(Vec2(0.5,0.5));
    quoteOfTheDay->setPosition(Vec2(quoteLayer->getContentSize().width * 0.5, quoteLayer->getContentSize().height * 0.5));
    quoteLayer->addChild(quoteOfTheDay);
    
}


void SideLayer::onKeyReleased(EventKeyboard::KeyCode keyCode, Event *pEvent)
{
    pEvent->stopPropagation();
    if(keyCode == EventKeyboard::KeyCode::KEY_BACK || keyCode == EventKeyboard::KeyCode::KEY_ESCAPE)
    {
        this->runExitAnimation();
    }
}

void SideLayer::onExit()
{
    CCLOG("On exit Main Scene called");
    listener->release();
    
    Layer::onExit();
    
}
