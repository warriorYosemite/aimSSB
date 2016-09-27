//
//  MainScene.cpp
//  AimSSB
//
//  Created by Machintosh on 27/09/16.
//
//

#include "MainScene.hpp"
#include "AppDelegate.h"
#include "constant.h"


USING_NS_CC_EXT;
using namespace std;

Scene* MainScene::createScene()
{
    
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = MainScene::create();
    
    // add layer as a child to scene
    scene->addChild(layer);
    
    // return the scene
    return scene;
}

bool MainScene::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }
    
    return true;
}

void MainScene::onEnter()
{
    
    Layer::onEnter();
    
    m_keyboardListener = NULL;
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
    m_keyboardListener->onKeyReleased = CC_CALLBACK_2(MainScene::onKeyReleased, this);
    Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(m_keyboardListener, this);
    
    createBackground();
    
    createPageView();
}

void MainScene::createBackground(){

    m_backgroundLayer = LayerColor::create(Color4B::WHITE, visibleSize.width, visibleSize.height);
    m_backgroundLayer->setPosition(Vec2(0,0));
    this->addChild(m_backgroundLayer);
    
    LayerColor* headerLayer = LayerColor::create(Color4B(51,64,28,255), visibleSize.width, visibleSize.height * 0.1);
    headerLayer->setPosition(Vec2(0, visibleSize.height - visibleSize.height * 0.1));
    this->addChild(headerLayer);
    
    Label* headerText = Label::createWithTTF("AIM SSB",FONT_ARM_WRESTLER,60);
    headerText->setPosition(Vec2(headerLayer->getContentSize().width * 0.5, headerLayer->getContentSize().height * 0.5));
    headerLayer->addChild(headerText);

}

void MainScene::createPageView(){

    m_pageView = ui::PageView::create();
    m_pageView->setContentSize(Size(visibleSize.width,visibleSize.height * 0.3));
    m_pageView->setAnchorPoint(Vec2(0.5,1));
    m_pageView->setPosition(Vec2(visibleSize.width * 0.5,visibleSize.height - visibleSize.height * 0.1));
    m_pageView->addEventListener(CC_CALLBACK_2(MainScene::pageViewEvent, this));
    m_pageView->setColor(Color3B::GRAY);
    
//    m_pageView->autoScroll(1);
    
    this->addChild(m_pageView , 3);
    
    
    m_numOfPages = 5;
    char str[100] = {0} ;
    for(int i=m_numOfPages; i>=1; i--)
    {
        auto pageLayout = ui::Layout::create();
        
        sprintf(str, "image%d.jpg",i);
        Sprite* imageToBeAdded = Sprite::create(str);
    
        Size ws = Size(visibleSize.width, visibleSize.height * 0.3);
        Size maskSize = ws* 0.975;
        
        float radius = 30;
        
        int scaleBoundsX = visibleSize.width;
        int scaleBoundY = visibleSize.height * 0.3;
        float scaleX = scaleBoundsX/imageToBeAdded->getContentSize().width;
        float scaleY = scaleBoundY/imageToBeAdded->getContentSize().height;
        imageToBeAdded->setScaleX(scaleX);
        imageToBeAdded->setScaleY(scaleY);
        
        // create masked image and position to center it on screen
        Node* clipNode = createRoundedRectMaskNode(maskSize, radius, 1.0f, 10);
        imageToBeAdded->setAnchorPoint(Vec2(0,0));
        clipNode->setAnchorPoint(Vec2(0,0));
        clipNode->addChild(imageToBeAdded);
        clipNode->setPosition(Vec2(10, pageLayout->getContentSize().height * 0.5));
        pageLayout->addChild(clipNode);
        m_pageView->addPage(pageLayout);
    }
    
}

void MainScene::pageViewEvent(cocos2d::Ref *pSender,cocos2d::ui::PageView::EventType type)
{
    CCLOG("inside pageview event sliderpage view");
    ssize_t currPage = m_pageView->getCurPageIndex();
    if (currPage == 8)
    {

    }
    else {

    }
    
    switch (type)
    {
        case cocos2d::ui::PageView::EventType::TURNING:
        {
            CCLOG("PAGE VIEW TURNING EVENT CALL BACK");
            cocos2d::ui::PageView* pageView = dynamic_cast<cocos2d::ui::PageView*>(pSender);
            break ;
        }
        default:
            
            break ;
    }
}

void MainScene::appendCubicBezier(int startPoint, std::vector<Vec2>& verts, const Vec2& from, const Vec2& control1, const Vec2& control2, const Vec2& to, uint32_t segments)
{
    float t = 0;
    for(int i = 0; i < segments; i++)
    {
        float x = powf(1 - t, 3) * from.x + 3.0f * powf(1 - t, 2) * t * control1.x + 3.0f * (1 - t) * t * t * control2.x + t * t * t * to.x;
        float y = powf(1 - t, 3) * from.y + 3.0f * powf(1 - t, 2) * t * control1.y + 3.0f * (1 - t) * t * t * control2.y + t * t * t * to.y;
        verts[startPoint + i] = Vec2(x,y);
        t += 1.0f / segments;
    }
}

Node* MainScene::createRoundedRectMaskNode(Size size, float radius, float borderWidth, int cornerSegments)
{
    const float kappa = 0.552228474;
    float oneMinusKappa = (1.0f-kappa);
    
    // define corner control points
    std::vector<Vec2> verts(16);
    
    verts[0] = Vec2(0, radius);
    verts[1] = Vec2(0, radius * oneMinusKappa);
    verts[2] = Vec2(radius * oneMinusKappa, 0);
    verts[3] = Vec2(radius, 0);
    
    verts[4] = Vec2(size.width - radius, 0);
    verts[5] = Vec2(size.width - radius * oneMinusKappa, 0);
    verts[6] = Vec2(size.width, radius * oneMinusKappa);
    verts[7] = Vec2(size.width, radius);
    
    verts[8] = Vec2(size.width, size.height - radius);
    verts[9] = Vec2(size.width, size.height - radius * oneMinusKappa);
    verts[10] = Vec2(size.width - radius * oneMinusKappa, size.height);
    verts[11] = Vec2(size.width - radius, size.height);
    
    verts[12] = Vec2(radius, size.height);
    verts[13] = Vec2(radius * oneMinusKappa, size.height);
    verts[14] = Vec2(0, size.height - radius * oneMinusKappa);
    verts[15] = Vec2(0, size.height - radius);
    
    // result
    std::vector<Vec2> polyVerts(4 * cornerSegments + 1);
    
    // add corner arc segments
    appendCubicBezier(0 * cornerSegments, polyVerts, verts[0], verts[1], verts[2], verts[3], cornerSegments);
    appendCubicBezier(1 * cornerSegments, polyVerts, verts[4], verts[5], verts[6], verts[7], cornerSegments);
    appendCubicBezier(2 * cornerSegments, polyVerts, verts[8], verts[9], verts[10], verts[11], cornerSegments);
    appendCubicBezier(3 * cornerSegments, polyVerts, verts[12], verts[13], verts[14], verts[15], cornerSegments);
    // close path
    polyVerts[4 * cornerSegments] = verts[0];
    
    // draw final poly into mask
    auto shapeMask = DrawNode::create();
    shapeMask->drawPolygon(&polyVerts[0], polyVerts.size(), Color4F::WHITE, 0.0f, Color4F::WHITE);
    
    // create clip node with draw node as stencil (mask)
    return ClippingNode::create(shapeMask);
}


void MainScene::onKeyReleased(EventKeyboard::KeyCode keyCode, Event *pEvent)
{
    pEvent->stopPropagation();
    if(keyCode == EventKeyboard::KeyCode::KEY_BACK || keyCode == EventKeyboard::KeyCode::KEY_ESCAPE)
    {
//        backButton(NULL);
    }
}

void MainScene::onExit()
{
    CCLOG("On exit Main Scene called");
    listener->release();
    
    Layer::onExit();
    
}










