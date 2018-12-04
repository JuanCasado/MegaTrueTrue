//
//  Basico.hpp
//  MegaTrueTrue
//
//  Created by Juan Casado Ballesteros on 10/30/18.
//

#ifndef Basico_hpp
#define Basico_hpp

#include "Conexion.hpp"
#include "ui/CocosGUI.h"
#include "AppDelegate.h"

class Basico : public cocos2d::Scene{
public:
    static Basico *create(Conexion *conexion, bool state);
private:
    Basico (Conexion *conexion, bool state);
    virtual bool init () override;
    Conexion *conexion;
    cocos2d::Vec2 lastTouch;
    bool isTouching;
    void update (float t) override;
    void setPortrait();
    void setLandscape();
    int speed;
    int turn;
    int count;
    int speed_a;
    int turn_a;
    int count_a;
    bool state;
    cocos2d::Label *speed_l;
    cocos2d::Label *turn_l;
    cocos2d::Label *title;
    cocos2d::Sprite *pulse;
    cocos2d::Sprite *circle;
    cocos2d::Color3B azul_oscuro = cocos2d::Color3B(60,0,255);
    cocos2d::ui::Button *button_azul_oscuro;
    cocos2d::Color3B azul_claro = cocos2d::Color3B(0,220,255);
    cocos2d::ui::Button *button_azul_claro;
    cocos2d::Color3B rojo = cocos2d::Color3B(255,50,0);
    cocos2d::ui::Button *button_rojo;
    cocos2d::Color3B verde = cocos2d::Color3B(0,255,100);
    cocos2d::ui::Button *button_verde;
    cocos2d::Color3B blanco = cocos2d::Color3B(255,255,255);
    cocos2d::ui::Button *button_blanco;
    cocos2d::Color3B amarillo = cocos2d::Color3B(255,255,0);
    cocos2d::ui::Button *button_amarillo;
    cocos2d::Color3B morado = cocos2d::Color3B(255,50,255);
    cocos2d::ui::Button *button_morado;
    cocos2d::ui::Button *c1;
    cocos2d::ui::Button *c2;
    cocos2d::ui::Button *c3;
    cocos2d::ui::Button *c4;
    cocos2d::ui::Button *c5;
    cocos2d::ui::Button *c6;
    cocos2d::ui::Button *c7;
    cocos2d::ui::Button *c8;
    cocos2d::ui::Button *c9;
    cocos2d::ui::Button *c10;
    cocos2d::ui::Button *c11;
    cocos2d::ui::Button *c12;
    cocos2d::Color3B music = cocos2d::Color3B(100,100,100);
};

#endif /* Basico_hpp */
