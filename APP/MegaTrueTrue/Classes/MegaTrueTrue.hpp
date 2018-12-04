//
//  MegaTrueTrue.hpp
//  MegaTrueTrue
//
//  Created by Juan Casado Ballesteros on 9/6/18.
//

#ifndef MegaTrueTrue_hpp
#define MegaTrueTrue_hpp

#include "cocos2d.h"
#include "Conexion.hpp"
#include "Basico.hpp"
#include "AppDelegate.h"

class MegaTrueTrue : public cocos2d::Scene {
public:
    static MegaTrueTrue* createScene();
private:
    virtual bool init();
    CREATE_FUNC(MegaTrueTrue);
    void update (float t);
    void setPortrait();
    void setLandscape();
    cocos2d::Label *title;
    cocos2d::Sprite *truetrue;
    float percentage;
    bool direction;
    cocos2d::ProgressTimer *countdownTimer;
    int timer;
    Conexion *connexion;
    ~MegaTrueTrue();
};

#endif /* MegaTrueTrue_hpp */
