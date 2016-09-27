#include "AppDelegate.h"
#include "SplashScene.h"
#include "AppMacros.h"
#include "MainScene.hpp"

USING_NS_CC;

AppDelegate* AppDelegate::m_instance = NULL;

AppDelegate::AppDelegate() {
    m_instance = this;
}

AppDelegate::~AppDelegate() 
{
}

AppDelegate* AppDelegate::getDelegate() {
    return m_instance;
}

//if you want a different context,just modify the value of glContextAttrs
//it will takes effect on all platforms
void AppDelegate::initGLContextAttrs()
{
    //set OpenGL context attributions,now can only set six attributions:
    //red,green,blue,alpha,depth,stencil
    GLContextAttrs glContextAttrs = {8, 8, 8, 8, 24, 8};

    GLView::setGLContextAttrs(glContextAttrs);
}

// If you want to use packages manager to install more packages, 
// don't modify or remove this function
static int register_all_packages()
{
    return 0; //flag for packages manager
}

bool AppDelegate::applicationDidFinishLaunching() {
    
    Device::setKeepScreenOn(true);
    
    // initialize director
    auto director = Director::getInstance();
    auto glview = director->getOpenGLView();
    if(!glview) {
        glview = GLViewImpl::create("My Game");
        director->setOpenGLView(glview);
    }
    
    
    Size frameSize = glview->getFrameSize();
    
    //Fix by height if iPad or a tablet which has double the width of our design size.
    //Else fix by width
    
    //    if ((frameSize.width / frameSize.height == 1.5)
    //        || frameSize.width / designResolutionSize.width > 2) {
    //        glview->setDesignResolutionSize(designResolutionSize.width,
    //                                        designResolutionSize.height, ResolutionPolicy::FIXED_HEIGHT);
    //    } else {
    //        glview->setDesignResolutionSize(designResolutionSize.width,
    //                                        designResolutionSize.height, ResolutionPolicy::FIXED_WIDTH);
    //    }
    
    if(frameSize.height/frameSize.width > 1.5) {
        glview->setDesignResolutionSize(designResolutionSize.width, designResolutionSize.height, ResolutionPolicy::FIXED_WIDTH);
        
    } else {
        glview->setDesignResolutionSize(designResolutionSize.width, designResolutionSize.height, ResolutionPolicy::FIXED_HEIGHT);
    }
    
    // turn on display FPS
    director->setDisplayStats(false);
    
    // set FPS. the default value is 1.0/60 if you don't call this
    director->setAnimationInterval(1.0 / 60);
    register_all_packages();


    // create a scene. it's an autorelease object
//    auto scene = SplashScene::createScene();
//    // run
//    director->runWithScene(scene);

    auto scene = MainScene::createScene();
    director->runWithScene(scene);
    
    return true;
}

// This function will be called when the app is inactive. When comes a phone call,it's be invoked too
void AppDelegate::applicationDidEnterBackground() {
    Director::getInstance()->stopAnimation();

    // if you use SimpleAudioEngine, it must be pause
    // SimpleAudioEngine::getInstance()->pauseBackgroundMusic();
}

// this function will be called when the app is active again
void AppDelegate::applicationWillEnterForeground() {
    Director::getInstance()->startAnimation();

    // if you use SimpleAudioEngine, it must resume here
    // SimpleAudioEngine::getInstance()->resumeBackgroundMusic();
}
