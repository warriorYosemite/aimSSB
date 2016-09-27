//
//  SideLayer.cpp
//  AimSSB
//
//  Created by Machintosh on 27/09/16.
//
//

#include "SideLayer.hpp"
#include "constant.h"

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
    
    createBackground();
    createContentLayer();
    
    runEnterAnimation();
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
