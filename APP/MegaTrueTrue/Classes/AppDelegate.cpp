#include "AppDelegate.h"

//#define USE_AUDIO_ENGINE 1
//#define USE_SIMPLE_AUDIO_ENGINE 1

#if USE_AUDIO_ENGINE && USE_SIMPLE_AUDIO_ENGINE
#error "Don't use AudioEngine and SimpleAudioEngine at the same time. Please just select one in your game!"
#endif

#if USE_AUDIO_ENGINE
#include "audio/include/AudioEngine.h"
using namespace cocos2d::experimental;
#elif USE_SIMPLE_AUDIO_ENGINE
#include "audio/include/SimpleAudioEngine.h"
using namespace CocosDenshion;
#endif

USING_NS_CC;

static cocos2d::Size designResolutionSize = cocos2d::Size(450, 800);
static cocos2d::Size smallResolutionSize = cocos2d::Size(320, 480);
static cocos2d::Size mediumResolutionSize = cocos2d::Size(768, 1024);
static cocos2d::Size largeResolutionSize = cocos2d::Size(1536, 2048);

AppDelegate::AppDelegate(){}

AppDelegate::~AppDelegate()
{
#if USE_AUDIO_ENGINE
    AudioEngine::end();
#elif USE_SIMPLE_AUDIO_ENGINE
    SimpleAudioEngine::end();
#endif
}

void AppDelegate::initGLContextAttrs(){
    GLContextAttrs glContextAttrs = {8, 8, 8, 8, 24, 8, 0};
    GLView::setGLContextAttrs(glContextAttrs);
}

static int register_all_packages()
{
    return 0;
}

bool AppDelegate::applicationDidFinishLaunching() {
    auto director = Director::getInstance();
    auto glview = director->getOpenGLView();
    if(!glview) {
        glview = GLViewImpl::createWithFullScreen("MegaTrueTrue");
        director->setOpenGLView(glview);
    }
    director->setAnimationInterval(1.0f / 60);
    
    if (getScreenOrientation ()){
        glview->setDesignResolutionSize(designResolutionSize.height, designResolutionSize.width, ResolutionPolicy::SHOW_ALL);
    } else {
        glview->setDesignResolutionSize(designResolutionSize.width, designResolutionSize.height, ResolutionPolicy::SHOW_ALL);
    }
    
    auto frameSize = glview->getFrameSize();
    if (frameSize.height > mediumResolutionSize.height){
        director->setContentScaleFactor(MIN(largeResolutionSize.height/designResolutionSize.height, largeResolutionSize.width/designResolutionSize.width));
    }else if (frameSize.height > smallResolutionSize.height){
        director->setContentScaleFactor(MIN(mediumResolutionSize.height/designResolutionSize.height, mediumResolutionSize.width/designResolutionSize.width));
    }else{
        director->setContentScaleFactor(MIN(smallResolutionSize.height/designResolutionSize.height, smallResolutionSize.width/designResolutionSize.width));
    }
    
    director->setClearColor(Color4F(0, 0, 0, 0));
    
    register_all_packages();
    auto megaTrueTrue = MegaTrueTrue::createScene();
    if (megaTrueTrue!=nullptr){
        director->runWithScene(megaTrueTrue);
    }
    return true;
}

void AppDelegate::applicationScreenSizeChanged(int newWidth, int newHeight)
{
    if (newWidth <= 0 || newHeight <= 0){
        return;
    }
    auto director = Director::getInstance();
    auto glview = director->getOpenGLView();
    if (glview){
        auto size = glview->getFrameSize();
        if (size.equals(Size(newWidth, newHeight))){
            return;
        }
        glview->setFrameSize(newWidth, newHeight);
        if (newWidth > newHeight){
            glview->setDesignResolutionSize(designResolutionSize.height, designResolutionSize.width, ResolutionPolicy::SHOW_ALL);
        } else {
            glview->setDesignResolutionSize(designResolutionSize.width, designResolutionSize.height, ResolutionPolicy::SHOW_ALL);
        }
    }
}

void AppDelegate::applicationDidEnterBackground() {
    Director::getInstance()->stopAnimation();
}

void AppDelegate::applicationWillEnterForeground() {
    Director::getInstance()->startAnimation();
}

bool AppDelegate::getScreenOrientation (){
    auto director = Director::getInstance();
    auto glview = director->getOpenGLView();
    auto size = glview->getFrameSize();
    return size.width > size.height;
}
