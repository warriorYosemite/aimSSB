//
//  ArticleLayer.cpp
//  AimSSB
//
//  Created by Machintosh on 30/09/16.
//
//

#include "ArticleLayer.hpp"

#include "constant.h"

using namespace cocos2d::extension;
using namespace std;
using namespace cocos2d::ui;

ArticleLayer* ArticleLayer::createLayer()
{
    
    // 'layer' is an autorelease object
    auto layer = ArticleLayer::create();
    
    
    // return the layer
    return layer;
}

// on "init" you need to initialize your instance
bool ArticleLayer::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }
    
    return true;
}

void ArticleLayer::onEnter()
{
    Layer::onEnter();
    m_keyboardListener = NULL;
    
    CCLOG("creating article layer");
    
    visibleSize = Director::getInstance()->getVisibleSize();
    
    auto dispatcher = Director::getInstance()->getEventDispatcher();
    listener = EventListenerTouchOneByOne::create();
    listener->onTouchBegan = [=](Touch* touch, Event* event){
        return true;
    };
    
    listener->setSwallowTouches(true);
    dispatcher->addEventListenerWithSceneGraphPriority(listener, this);
    listener->retain();
    
    m_keyboardListener = EventListenerKeyboard::create();
    m_keyboardListener->onKeyReleased = CC_CALLBACK_2(ArticleLayer::onKeyReleased, this);
    Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(m_keyboardListener, this);
    
    
    createBackground();
    
    createScrollView();

}

//void ArticleLayer::scrollViewDidScroll(ScrollView* view)
//{
//
//
//}

void ArticleLayer::createScrollView(){

    Size scollFrameSize = Size(visibleSize.width - 30.f, visibleSize.height - 10.f);
    m_scrollView = cocos2d::ui::ScrollView::create();
    m_scrollView->setContentSize(scollFrameSize);
    m_scrollView->setBackGroundColorType(cocos2d::ui::Layout::BackGroundColorType::NONE);
    m_scrollView->setBackGroundColor(Color3B(200, 200, 200));
    m_scrollView->setPosition(Point(15, 5));
    m_scrollView->setDirection(cocos2d::ui::ScrollView::Direction::VERTICAL);
    
    auto containerSize = Size(scollFrameSize.width, scollFrameSize.height * 2);
    m_scrollView->setInnerContainerSize(containerSize);
    
    m_scrollView->setBounceEnabled(true);
    m_scrollView->setTouchEnabled(true);
    m_scrollView->setScrollBarEnabled(true);
    m_scrollView->setScrollBarColor(Color3B::BLACK);
    m_scrollView->setScrollBarWidth(20);
    m_scrollView->setInnerContainerSize(containerSize);
    this->addChild(m_scrollView, 2);


}
void ArticleLayer::createBackground(){
    
    m_backgroundLayer = LayerColor::create(Color4B::Color4B(200,200,209,255), visibleSize.width, visibleSize.height);
    m_backgroundLayer->setPosition(Vec2(0,0));
    this->addChild(m_backgroundLayer);
    
}

void ArticleLayer::onExit()
{
    CCLOG("On exit Article Layer called");
    listener->release();
    Layer::onExit();
    
}

void ArticleLayer::onKeyReleased(EventKeyboard::KeyCode keyCode, Event *pEvent)
{
    pEvent->stopPropagation();
    if(keyCode == EventKeyboard::KeyCode::KEY_BACK || keyCode == EventKeyboard::KeyCode::KEY_ESCAPE)
    {
        this->removeFromParentAndCleanup(true);
    }
}

