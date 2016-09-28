//  Created by Kuldeep Teekas
//  Dated : 08-09-2015
//


#include "ContentLayer.h"
#include "AppDelegate.h"


using namespace cocos2d::extension;
using namespace std;

#define HEADER_LABEL_TAG                    213
#define CELL_BG_TAG                         214


ContentLayer* ContentLayer::createLayer(float width, float height)
{
    
    // 'layer' is an autorelease object
    auto layer = ContentLayer::create();
    layer->setContentSize(Size(width, height));
    
    // return the scene
    return layer;
}


// on "init" you need to initialize your instance
bool ContentLayer::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }
    return true;
}

void ContentLayer::onEnter()
{
    
    Layer::onEnter();
    
    visibleSize = Director::getInstance()->getVisibleSize();
    
    createBackground();
    createTableView();
    
}

void ContentLayer::createTableView(){
    
    tableWidth = this->getContentSize().width;
    tableHeight = this->getContentSize().height;
    
    
    m_tableView = cocos2d::extension::TableView::create(this, Size(tableWidth,tableHeight));
    m_tableView->setDirection(cocos2d::extension::TableView::Direction::VERTICAL);
    m_tableView->setPosition(Vec2(0,0));
    m_tableView->setDelegate(this);
    m_tableView->setVerticalFillOrder(cocos2d::extension::TableView::VerticalFillOrder::TOP_DOWN);
    this->addChild(m_tableView);

}

Size ContentLayer::tableCellSizeForIndex(cocos2d::extension::TableView *table, ssize_t idx)
{
    rowHeight = 150;
    return Size(tableWidth, rowHeight);
}

void ContentLayer::tableCellTouched(TableView *table, TableViewCell *cell)
{
    
    CCLOG("CELL %zd ", cell->getIdx());
    
    int idx = (int)cell->getIdx();

}

TableViewCell* ContentLayer::tableCellAtIndex(TableView *table, ssize_t idx)
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

    //as notifications and latest post have same type, hence using same kind of container
    if (m_contentType == CONTENT_LATEST_POST || m_contentType == CONTENT_NOTIFICATIONS){
        
        std::string imagePath = m_contentList.at(idx)->m_imageURL;
        std::string headingText = m_contentList.at(idx)->m_heading;
        std::string contentText = m_contentList.at(idx)->m_content;
        
        LayerColor* cellBg = LayerColor::create(Color4B(255,255,255,200), tableWidth, rowHeight - 7);
        cellBg->setTag(CELL_BG_TAG);
        cellBg->setPosition(Vec2(0,0));
        cell->addChild(cellBg);
        
        Sprite* contentImage = NULL;
        
        if (!imagePath.empty()){
        
            contentImage = Sprite::create(imagePath);
            
        }else{
        
            contentImage = Sprite::create("default_image.png");
        }
        
        int scaleBoundsX = 150;
        int scaleBoundY = 120;
        
        Size ws = Size(scaleBoundsX, scaleBoundY);
        Size maskSize = ws;
        
        float radius = 15;
        
        float scaleX = scaleBoundsX/contentImage->getContentSize().width;
        float scaleY = scaleBoundY/contentImage->getContentSize().height;
        contentImage->setScaleX(scaleX);
        contentImage->setScaleY(scaleY);
        
        float yPosition = (cellBg->getContentSize().height - scaleBoundY) * 0.5;
        
        // create masked image and position to center it on screen
        Node* clipNode = AppDelegate::getDelegate()->createRoundedRectMaskNode(maskSize, radius, 1.0f, 10);
        contentImage->setAnchorPoint(Vec2(0,0));
        clipNode->setAnchorPoint(Vec2(0,0));
        clipNode->addChild(contentImage);
        clipNode->setPosition(Vec2(25,yPosition));
        cellBg->addChild(clipNode);
        
        std::string formattedHeadline = AppDelegate::getDelegate()->getTrimmedStringWithRange(headingText, 80);
        formattedHeadline.insert(40,"-\n");
        
        Label* headline = Label::createWithTTF(formattedHeadline, FONT_HEADLINE, 20);
        headline->setAnchorPoint(Vec2(0, 0.5));
        headline->setColor(Color3B::BLACK);
        headline->setPosition(Vec2(200, cellBg->getContentSize().height * 0.75));
        cellBg->addChild(headline);
        
        std::string formattedContent = "";
        
        if (!contentText.empty() && contentText.size() > 80){
            formattedContent = AppDelegate::getDelegate()->getTrimmedStringWithRange(contentText, 80);
            formattedContent.insert(42,"-\n");
        }
        
        Label* contentLine = Label::createWithTTF(formattedContent, FONT_CONTENT, 20);
        contentLine->setAnchorPoint(Vec2(0, 0.5));
        contentLine->setColor(Color3B::GRAY);
        contentLine->setPosition(Vec2(200, cellBg->getContentSize().height * 0.4));
        cellBg->addChild(contentLine);
        
    }
    else if (m_contentType == CONTENT_SSB_GUIDE){
    
    
    }
    return cell;
    
}
ssize_t ContentLayer::numberOfCellsInTableView(TableView *table)
{
    int size = (int)m_contentList.size();
    return size;
}

void ContentLayer::createBackground()
{
    LayerColor* bgLayer = LayerColor::create(Color4B(221,221,207, 255), this->getContentSize().width, this->getContentSize().height);
    bgLayer->setPosition(Vec2(0,0));
    this->addChild(bgLayer);
}

void ContentLayer::setContentType(CONTENT_TYPE contentType){
    
    m_contentType = contentType;
}

void ContentLayer::setContentList(std::vector<ItemsDetailStruct*> contentList, bool isReload){

    m_contentList.clear();
    
    for (auto temp : contentList){
    
        ItemsDetailStruct* elem1 = new ItemsDetailStruct();
        elem1->m_imageURL = temp->m_imageURL;
        elem1->m_heading = temp->m_heading;
        elem1->m_content = temp->m_content;
        m_contentList.push_back(elem1);
    }
    
    if (isReload){
    
        m_tableView->reloadData();
    }
}

void ContentLayer::onExit()
{
    Layer::onExit();
}
