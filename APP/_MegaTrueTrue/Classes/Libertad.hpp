//
//  Libertad.hpp
//  MegaTrueTrue
//
//  Created by Juan Casado Ballesteros on 9/8/18.
//

#ifndef Libertad_hpp
#define Libertad_hpp

#include "Conexion.hpp"
#include "ui/CocosGUI.h"
#include "MainMenu.hpp"

class Libertad : public cocos2d::Scene{
public:
    static Libertad *create(Conexion *conexion);
private:
    Libertad (Conexion *conexion);
    virtual bool init () override;
    Conexion *conexion;
    cocos2d::Vec2 lastTouch;
    bool isTouching;
    void update (float t) override;
    int speed;
    int turn;
    cocos2d::Label *speed_l;
    cocos2d::Label *turn_l;
    cocos2d::Vec2 center;
    cocos2d::Sprite *pulse;
};

#endif /* Libertad_hpp */
