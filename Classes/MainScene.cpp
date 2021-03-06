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
#include "ArticleLayer.hpp"

USING_NS_CC_EXT;
using namespace std;

int curPageIndex;


#define FONT_SIZE_MENUITEM                  27


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
    contentLayerE = NULL;
    isReverse = false;
    m_currContentType = CONTENT_LATEST_POST;
    
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
    setDataLatestItem();
    setDataNotificationItem();
    setSSBGuideList();
    
    createMenuItems();
    createContentHolder();
    
    Node::onEnter();
    curPageIndex = 0;
    this->schedule(CC_SCHEDULE_SELECTOR(MainScene::updatePages), 3);
}


void MainScene::createContentHolder(){
    
    contentLayerE = ContentLayer::createLayer(visibleSize.width , visibleSize.height * 0.5);
    contentLayerE->setPosition(Vec2(0,0));
    contentLayerE->setContentType(CONTENT_LATEST_POST);
    contentLayerE->setContentList(m_latestItemsList, false);
    this->addChild(contentLayerE);
}

void MainScene::updatePages(float dt){
    
    if (curPageIndex == m_numOfPages -1){
        isReverse = true;
    }
    else if (curPageIndex == 0){
    
        isReverse = false;
    }
    
    if (!isReverse){
        curPageIndex++;
    }else{
        
        curPageIndex--;
    }
    
    m_pageView->scrollToPage(curPageIndex);
}


void MainScene::createBackground(){

    m_backgroundLayer = LayerColor::create(Color4B::WHITE, visibleSize.width, visibleSize.height);
    m_backgroundLayer->setPosition(Vec2(0,0));
    this->addChild(m_backgroundLayer);
    
    LayerColor* headerLayer = LayerColor::create(Color4B(51,64,28,255), visibleSize.width, visibleSize.height * 0.1);
    headerLayer->setPosition(Vec2(0, visibleSize.height - visibleSize.height * 0.1));
    this->addChild(headerLayer);
    
    Label* headerText = Label::createWithTTF("AIM SSB",FONT_HEADLINE,60);
    headerText->setPosition(Vec2(headerLayer->getContentSize().width * 0.5, headerLayer->getContentSize().height * 0.5));
    headerLayer->addChild(headerText);
    
    Sprite* listSprite =  Sprite::create("list.png");
    MenuItemSprite* listItem = MenuItemSprite::create(listSprite, listSprite,CC_CALLBACK_1(MainScene::listItemCallback, this));
    
    auto listMenu = Menu::create(listItem, NULL);
    listMenu->setPosition(Vec2(listItem->getContentSize().width, headerLayer->getContentSize().height * 0.5));
    headerLayer->addChild(listMenu);
    
    Sprite* shareImage =  Sprite::create("share.png");
    MenuItemSprite* shareItem = MenuItemSprite::create(shareImage, shareImage,CC_CALLBACK_1(MainScene::shareItemCallBack, this));
    
    auto shareMenu = Menu::create(shareItem, NULL);
    shareMenu->setPosition(Vec2(headerLayer->getContentSize().width - shareItem->getContentSize().width * 0.7, headerLayer->getContentSize().height * 0.5));
    headerLayer->addChild(shareMenu);

}

void MainScene::createMenuItems(){

    Scale9Sprite* menuImage1 = Scale9Sprite::create("scaleableImage.png");
    Scale9Sprite* menuImage2 = Scale9Sprite::create("scaleableImage.png");
    Scale9Sprite* menuImage3 = Scale9Sprite::create("scaleableImage.png");
    
    Scale9Sprite* menuImage1Pressed = Scale9Sprite::create("scaleableImage.png");
    Scale9Sprite* menuImage2Pressed = Scale9Sprite::create("scaleableImage.png");
    Scale9Sprite* menuImage3Pressed = Scale9Sprite::create("scaleableImage.png");
    
    
    
    float imageWidth = visibleSize.width * 0.3;
    float imageHeight = 70;
    
    menuImage1->setContentSize(Size(imageWidth, imageHeight));
    menuImage2->setContentSize(Size(imageWidth, imageHeight));
    menuImage3->setContentSize(Size(imageWidth, imageHeight));
    
    menuImage1Pressed->setContentSize(Size(imageWidth, imageHeight));
    menuImage2Pressed->setContentSize(Size(imageWidth, imageHeight));
    menuImage3Pressed->setContentSize(Size(imageWidth, imageHeight));
    
    menuImage1Pressed->setScale(0.95);
    menuImage2Pressed->setScale(0.95);
    menuImage3Pressed->setScale(0.95);
    
    Label* latestLabel = Label::createWithTTF("Latest Post", FONT_HEADLINE, FONT_SIZE_MENUITEM);
    latestLabel->setPosition(Vec2(menuImage1->getContentSize().width * 0.5, menuImage1->getContentSize().height * 0.5));
    menuImage1->addChild(latestLabel);
    
    Label* ssbLabel = Label::createWithTTF("SSB Guide", FONT_HEADLINE, FONT_SIZE_MENUITEM);
    ssbLabel->setPosition(Vec2(menuImage2->getContentSize().width * 0.5, menuImage2->getContentSize().height * 0.5));
    menuImage2->addChild(ssbLabel);
    
    Label* notificationLabel = Label::createWithTTF("Notifications", FONT_HEADLINE, FONT_SIZE_MENUITEM);
    notificationLabel->setPosition(Vec2(menuImage3->getContentSize().width * 0.5, menuImage3->getContentSize().height * 0.5));
    menuImage3->addChild(notificationLabel);
    
    //for pressed effect
    Label* latestLabel2 = Label::createWithTTF("Latest Post", FONT_HEADLINE, FONT_SIZE_MENUITEM - 1);
    latestLabel2->setPosition(Vec2(menuImage1Pressed->getContentSize().width * 0.5, menuImage1Pressed->getContentSize().height * 0.5));
    menuImage1Pressed->addChild(latestLabel2);
    
    Label* ssbLabel2 = Label::createWithTTF("SSB Guide", FONT_HEADLINE, FONT_SIZE_MENUITEM - 1);
    ssbLabel2->setPosition(Vec2(menuImage2Pressed->getContentSize().width * 0.5, menuImage2Pressed->getContentSize().height * 0.5));
    menuImage2Pressed->addChild(ssbLabel2);
    
    Label* notificationLabel2 = Label::createWithTTF("Notifications", FONT_HEADLINE, FONT_SIZE_MENUITEM - 1);
    notificationLabel2->setPosition(Vec2(menuImage3Pressed->getContentSize().width * 0.5, menuImage3Pressed->getContentSize().height * 0.5));
    menuImage3Pressed->addChild(notificationLabel2);
    
    
    latestPostItem = MenuItemSprite::create(menuImage1, menuImage1Pressed, CC_CALLBACK_1(MainScene::latestPostCallBack,this));
    ssbGuideItem = MenuItemSprite::create(menuImage2, menuImage2Pressed, CC_CALLBACK_1(MainScene::ssbGuideCallBack,this));
    notificationItem = MenuItemSprite::create(menuImage3, menuImage3Pressed, CC_CALLBACK_1(MainScene::notificationCallBack,this));
    
    this->gameSelectionMenuItems.pushBack(latestPostItem);
    this->gameSelectionMenuItems.pushBack(ssbGuideItem);
    this->gameSelectionMenuItems.pushBack(notificationItem);
    
    latestPostItem->setPosition(Vec2(latestPostItem->getContentSize().width * 0.6, visibleSize.height * 0.55));
    ssbGuideItem->setPosition(Vec2(visibleSize.width * 0.5, visibleSize.height * 0.55));
    notificationItem->setPosition(Vec2(visibleSize.width - notificationItem->getContentSize().width * 0.6, visibleSize.height * 0.55));
    
    auto menu = Menu::createWithArray(gameSelectionMenuItems);
    CCLOG("menu created");
    menu->setPosition(Point::ZERO);
    this->addChild(menu);

}

void MainScene::setDataLatestItem(){

    ItemsDetailStruct* item1 = new ItemsDetailStruct();
    item1->m_heading = "Uri attack: Security agencies suspect LeT hand,seized maps depict local topography";
    item1->m_content = "Uri (J&K): Two maps depicting the general topography of Uri were recovered from the four terrorists who stormed into an Army camp here even as the army intensified efforts to identify the exact stretch along the Line of Control (LoC) from where they entered India. \n \n Official sources said today that besides arms and ammunition, two maps showing general area of Uri were recovered from the four slain terrorists, who are now believed to be from Pakistan-based Lashker-e-Taiba(LeT). \n \n The maps showed various places of Uri including the Brigade Headquarters and other installations of this town, about 75 km North of Srinagar. \n \n The place is strategically important in view of the power project operated by National Hydel Power Corporation(NHPC) \n \n In the meantime, Army has contacted heads of 12 villages located above the Brigade headquarters to ascertain whether they could throw some light about the infiltration, the sources said, adding this was a part of domination drill being conducted by the army off and on along the LoC. \n \n The army was conducting search operations in various villages along the LoC to find out whether the four terrorists, who carried out the audacious attack at the camp on September 18, had left tell-tale signs. There were reports that that Army had intensified searches in Charunda and Gollahan villages to ascertain whether the terrorists had taken shelter before reaching the army camp at Uri. Both the villages have a combined household of 603 and a population of less than 4,000. \n \n  The Jammu and Kashmir Police has handed over to NIA the call details and internet data usage of all active cellphones and broadband connections in Uri town for he period of 24 hours prior to daring attack on the army base, the sources said. \n \n  The NIA team, which arrived here on Tuesday, today finished the documentation process which includes seizure of the arms, ammunition and other articles.\n \n  The NIA along with technical experts from other security agencies is also trying to retrieve data from the Global Positioning System (GPS) sets recovered from the slain militants. \n \n  The NIA Tuesday registered a case to probe the terror attack at the Army installation in Uri. \n \n The NIA team would prepare a dossier and may make a formal request to Pakistan once the identity of the four was ascertained. \n \n Army has also instituted an inquiry into the attack with preliminary investigation suggesting the terrorists had entered the area at least a day before mounting the brazen assault. \n \n The inquiry besides ascertaining lapses, if any, would also suggest measures to prevent such attacks in the future as Pakistani-based groups were indulging more in shallow infiltration, which means that terrorists strike the first available installation after crossing the LoC.";
    
    item1->m_imageURL = "latest.jpg";
    
    m_latestItemsList.push_back(item1);
    
    ItemsDetailStruct* item2 = new ItemsDetailStruct();
    item2->m_heading = "At 10, Burhan Wani wanted to join Indian Army, says father";
    item2->m_content = "Muzaffar Wani, the father of slain Hizbul Mujahideen commander Burhan Wani, whose encounter death triggered the continuing cycle of violence in Kashmir.";
    
    item2->m_imageURL = "latest2.jpg";
    m_latestItemsList.push_back(item2);
    
    ItemsDetailStruct* item3 = new ItemsDetailStruct();
    item3->m_heading = "PM Modi Won't Go To Pak, 3 Other Nations Join India In Boycott: 10 Facts";
    item3->m_content = "Within hours of Prime Minister Narendra Modi confirming he will not attend a regional SAARC summit in Pakistan, three other countries have opted out of the November session, which will have to be re-located.";
    
    item3->m_imageURL = "latest3.jpg";
    m_latestItemsList.push_back(item3);
    
    ItemsDetailStruct* item4 = new ItemsDetailStruct();
    item4->m_heading = "INS Viraat: History of the world’s oldest aircraft carrier";
    item4->m_content = "After 29 years of service to the Indian Navy, the world’s oldest aircraft carrier INS Viraat is set to bid adieu.";
    
    item4->m_imageURL = "latest4.jpg";
    m_latestItemsList.push_back(item4);
    
    ItemsDetailStruct* item5 = new ItemsDetailStruct();
    item5->m_heading = "After MNS threat, MS Dhoni: The Untold Story boycotted in Pakistan";
    item5->m_content = "Pakistani distributors have decided not to release MS Dhoni biopic, MS Dhoni: The Untold Story.";
    
    item5->m_imageURL = "latest5.jpg";
    m_latestItemsList.push_back(item5);

}

void MainScene::setSSBGuideList(){

    ItemsDetailStruct* item1 = new ItemsDetailStruct();
    item1->m_heading = "INTRODUCTION";
    m_ssbGuideItemsList.push_back(item1);
    
    ItemsDetailStruct* item2 = new ItemsDetailStruct();
    item2->m_heading = "SCREENING";
    m_ssbGuideItemsList.push_back(item2);
    
    ItemsDetailStruct* item3 = new ItemsDetailStruct();
    item3->m_heading = "PSYCHOLOGICAL TEST";
    m_ssbGuideItemsList.push_back(item3);
    
    ItemsDetailStruct* item4 = new ItemsDetailStruct();
    item4->m_heading = "GTO";
    m_ssbGuideItemsList.push_back(item4);
    
    ItemsDetailStruct* item5 = new ItemsDetailStruct();
    item5->m_heading = "PERSONAL INTERVIEW";
    m_ssbGuideItemsList.push_back(item5);
    
    ItemsDetailStruct* item6 = new ItemsDetailStruct();
    item6->m_heading = "CONFERENCE";
    m_ssbGuideItemsList.push_back(item6);

}

void MainScene::setDataNotificationItem(){

    ItemsDetailStruct* item1 = new ItemsDetailStruct();
    item1->m_heading = "Indian Army 10+2 TES 2016 Apply Online for 90 Posts";
    item1->m_imageURL = "notification1.jpg";
    
    m_notificationsItemsList.push_back(item1);
    
    ItemsDetailStruct* item2 = new ItemsDetailStruct();
    item2->m_heading = "On 8 January 2009 the Indian Naval Academy, was inaugurated by then prime minister Manmohan Singh";
    item2->m_imageURL = "notification2.jpg";
    
    m_notificationsItemsList.push_back(item2);
    
    ItemsDetailStruct* item3 = new ItemsDetailStruct();
    item3->m_heading = "The Siachen Glacier, 5000 metres above sea level, is the highest battlefield in the world. And the Indian Army controls it.";
    item3->m_imageURL = "notification3.jpg";
    
    m_notificationsItemsList.push_back(item3);
    
    ItemsDetailStruct* item4 = new ItemsDetailStruct();
    item4->m_heading = "Soldiers of the Indian Army are considered among the best in jungle warfare.";
    item4->m_imageURL = "notification4.jpg";
    
    m_notificationsItemsList.push_back(item4);
    
    
}



void MainScene::createArticleLayer(ItemsDetailStruct* data){

    if (m_currContentType == CONTENT_SSB_GUIDE){
    
        return;
    }
    
    ArticleLayer* articleLayer = ArticleLayer::createLayer();
    articleLayer->setDataElement(data);
    articleLayer->setPosition(Vec2(0,0));
    this->addChild(articleLayer, 10);

}
void MainScene::latestPostCallBack(Ref* pSender){

    CCLOG("Inside latest post callback");
    
    m_currContentType = CONTENT_LATEST_POST;
    
    contentLayerE->setContentType(CONTENT_LATEST_POST);
    contentLayerE->setContentList(m_latestItemsList, true);

}

void MainScene::ssbGuideCallBack(Ref* pSender){

    CCLOG("Inside ssb Guide callback");
    
    m_currContentType = CONTENT_SSB_GUIDE;
    
    contentLayerE->setContentType(CONTENT_SSB_GUIDE);
    contentLayerE->setContentList(m_ssbGuideItemsList, true);

}

void MainScene::notificationCallBack(Ref* pSender){

    CCLOG("Inside notifications callback");
    m_currContentType = CONTENT_NOTIFICATIONS;
    
    contentLayerE->setContentType(CONTENT_NOTIFICATIONS);
    contentLayerE->setContentList(m_notificationsItemsList, true);
    
}

void MainScene::shareItemCallBack(Ref* pSender){

    CCLOG("Inside share item callback");
    
}

void MainScene::listItemCallback(Ref* pSender){

    CCLOG("inside list item callback");
    SideLayer* sideLayerE = SideLayer::createLayer();
    this->addChild(sideLayerE, 2);

}

void MainScene::createPageView(){

    m_pageView = ui::PageView::create();
    m_pageView->setContentSize(Size(visibleSize.width,visibleSize.height * 0.3));
    m_pageView->setAnchorPoint(Vec2(0.5,1));
    m_pageView->setPosition(Vec2(visibleSize.width * 0.5,visibleSize.height - visibleSize.height * 0.1));
    m_pageView->addEventListener(CC_CALLBACK_2(MainScene::pageViewEvent, this));
    m_pageView->setColor(Color3B::GRAY);
    this->addChild(m_pageView, 1 );
    
    
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
        Node* clipNode = AppDelegate::getDelegate()->createRoundedRectMaskNode(maskSize, radius, 1.0f, 10);
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

void MainScene::onKeyReleased(EventKeyboard::KeyCode keyCode, Event *pEvent)
{
    pEvent->stopPropagation();
    if(keyCode == EventKeyboard::KeyCode::KEY_BACK || keyCode == EventKeyboard::KeyCode::KEY_ESCAPE)
    {
        Director::getInstance()->end();
    }
}

void MainScene::onExit()
{
    CCLOG("On exit Main Scene called");
    listener->release();
    
    Layer::onExit();
    
}