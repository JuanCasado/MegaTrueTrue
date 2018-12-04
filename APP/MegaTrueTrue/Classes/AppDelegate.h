#ifndef  _APP_DELEGATE_H_
#define  _APP_DELEGATE_H_

#include "cocos2d.h"
#include "MegaTrueTrue.hpp"

class  AppDelegate : private cocos2d::Application
{
public:
    AppDelegate();
    virtual ~AppDelegate();
    virtual void initGLContextAttrs();
    virtual bool applicationDidFinishLaunching();
    virtual void applicationDidEnterBackground();
    virtual void applicationWillEnterForeground();
    void applicationScreenSizeChanged(int newWidth, int newHeight);
    static bool getScreenOrientation ();
};

#endif // _APP_DELEGATE_H_

