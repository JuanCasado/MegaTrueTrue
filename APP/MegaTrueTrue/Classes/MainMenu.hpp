//
//  MainMenu.hpp
//  MegaTrueTrue
//
//  Created by Juan Casado Ballesteros on 9/8/18.
//

#ifndef MainMenu_hpp
#define MainMenu_hpp

#include "cocos2d.h"
#include "Conexion.hpp"
#include <vector>
#include "Odometria.hpp"
#include "Libertad.hpp"
#include "Configuracion.hpp"

class MainMenu : public cocos2d::Scene{
public:
    static MainMenu *create(Conexion *conexion);
private:
    MainMenu (Conexion *conexion);
    virtual bool init () override;
    Conexion *conexion;
    void odometriaClicked ();
    void libertadClicked ();
    void configuracionClicked ();
    cocos2d::MenuItemSprite *createButton(const char *txt,const cocos2d::ccMenuCallback &callback);
    cocos2d::Sprite *btt;
    cocos2d::Sprite *btt_clk;
    cocos2d::Color3B buttonColor;
    cocos2d::Size buttonSize;
};

#endif /* MainMenu_hpp */
