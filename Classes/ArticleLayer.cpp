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
    
    createBackButton();
    
    createReadContent();
    
    updateContent(true);

}

//void ArticleLayer::scrollViewDidScroll(ScrollView* view)
//{
//
//
//}

void ArticleLayer::createReadContent(){

    m_contentImage = Sprite::create(IMAGE_PATH"defaultContent.jpg");
    m_contentImage->setPosition(Vec2(m_scrollView->getContentSize().width * 0.5, containerSize.height - m_contentImage->getContentSize().height * 0.65));
    m_scrollView->addChild(m_contentImage);
    
    m_headerLine = Label::createWithTTF("", FONT_LIBRE, 30);
    m_headerLine->setAnchorPoint(Vec2(0, 1));
    m_headerLine->setColor(Color3B::BLACK);
    m_headerLine->setWidth(m_scrollView->getContentSize().width * 0.95);
    m_headerLine->setPosition(Vec2(10, m_contentImage->getPositionY() - m_contentImage->getContentSize().height * 0.52));
    m_scrollView->addChild(m_headerLine);
    
    m_contentPara = Label::createWithTTF("", FONT_ROBOTO_LIGHT, 20);
    m_contentPara->setAnchorPoint(Vec2(0, 1));
    m_contentPara->setColor(Color3B::BLACK);
    m_contentPara->setAdditionalKerning(1.2);
    m_contentPara->setWidth(m_scrollView->getContentSize().width * 0.95);
    m_contentPara->setPosition(Vec2(10, m_contentImage->getPositionY() - m_contentImage->getContentSize().height * 0.8));
    m_scrollView->addChild(m_contentPara);


}

void ArticleLayer::setDataElement(ItemsDetailStruct* tempData){

    if (tempData!= NULL){
    
        m_dataElement = new ItemsDetailStruct();
        m_dataElement->m_imageURL = tempData->m_imageURL;
        m_dataElement->m_heading = tempData->m_heading;
        m_dataElement->m_content = tempData->m_content;
    }

}

void ArticleLayer::updateContent(bool isUpdate){

    if (isUpdate){
    
        std::string imagePath = m_dataElement->m_imageURL;
        if (!imagePath.empty()){
            
            Sprite* tempImage = Sprite::create(imagePath);
            m_contentImage->setTexture(tempImage->getTexture());
        }
        
        std::string header = m_dataElement->m_heading;
        if(!header.empty()){
        
            m_headerLine->setString(header);
        }
    
        std::string paragraph = m_dataElement->m_content;
        if(!paragraph.empty()){
            
            m_contentPara->setString(paragraph);
        }
    }

}

void ArticleLayer::createScrollView(){

    Size scollFrameSize = Size(visibleSize.width - 30.f, visibleSize.height - 10.f);
    m_scrollView = cocos2d::ui::ScrollView::create();
    m_scrollView->setContentSize(scollFrameSize);
    m_scrollView->setBackGroundColorType(cocos2d::ui::Layout::BackGroundColorType::NONE);
    m_scrollView->setBackGroundColor(Color3B(200, 200, 200));
    m_scrollView->setPosition(Point(15, 5));
    m_scrollView->setDirection(cocos2d::ui::ScrollView::Direction::VERTICAL);
    
    containerSize = Size(scollFrameSize.width, scollFrameSize.height * 2.5);
    m_scrollView->setInnerContainerSize(containerSize);
    
    m_scrollView->setBounceEnabled(true);
    m_scrollView->setTouchEnabled(true);
    m_scrollView->setScrollBarEnabled(true);
    m_scrollView->setScrollBarColor(Color3B::BLACK);
    m_scrollView->setScrollBarWidth(8);
    m_scrollView->setInnerContainerSize(containerSize);
    this->addChild(m_scrollView, 2);

}

void ArticleLayer::createBackButton(){
    
    MenuItemImage* backButtonImage = MenuItemImage::create(ICON_PATH"cancel.png", ICON_PATH"cancel.png",
                                            CC_CALLBACK_1(ArticleLayer::backButton, this));
    backButtonImage->setAnchorPoint(Vec2(0.5,0.5));
    
    auto backButton = Menu::create(backButtonImage, NULL);
    backButton->setPosition(Vec2(backButtonImage->getContentSize().width * 0.6,
                                 this->getContentSize().height - backButtonImage->getContentSize().height * 0.5));
    this->addChild(backButton, 30);

}

void ArticleLayer::createBackground(){
    
    m_backgroundLayer = LayerColor::create(Color4B(255,255,255,255), visibleSize.width, visibleSize.height);
    m_backgroundLayer->setPosition(Vec2(0,0));
    this->addChild(m_backgroundLayer);
    
}

void ArticleLayer::onExit()
{
    CCLOG("On exit Article Layer called");
    listener->release();
    Layer::onExit();
    
}
void ArticleLayer::backButton(Ref* pSender){

    this->removeFromParentAndCleanup(true);
}

void ArticleLayer::onKeyReleased(EventKeyboard::KeyCode keyCode, Event *pEvent)
{
    pEvent->stopPropagation();
    if(keyCode == EventKeyboard::KeyCode::KEY_BACK || keyCode == EventKeyboard::KeyCode::KEY_ESCAPE)
    {
        backButton(NULL);
    }
}

