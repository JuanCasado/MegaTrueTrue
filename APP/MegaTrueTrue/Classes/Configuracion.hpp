//
//  Configuracion.hpp
//  MegaTrueTrue
//
//  Created by Juan Casado Ballesteros on 9/8/18.
//

#ifndef Configuracion_hpp
#define Configuracion_hpp

#include "Conexion.hpp"
#include "ui/CocosGUI.h"
#include "MainMenu.hpp"
#include <vector>

class Configuracion : public cocos2d::Scene{
public:
    static Configuracion *create(Conexion *conexion);
private:
    Configuracion (Conexion *conexion);
    virtual bool init () override;
    Conexion *conexion;
    cocos2d::Sprite *velMaxBackgroudStill;
    cocos2d::ui::TextField *velMaxField;
    cocos2d::Sprite *velMinBackgroudStill;
    cocos2d::ui::TextField *velMinField;
    cocos2d::Sprite *PodomDBackgroudStill;
    cocos2d::ui::TextField *PodomDField;
    cocos2d::Sprite *IodomDBackgroudStill;
    cocos2d::ui::TextField *IodomDField;
    cocos2d::Sprite *PodomIBackgroudStill;
    cocos2d::ui::TextField *PodomIField;
    cocos2d::Sprite *IodomIBackgroudStill;
    cocos2d::ui::TextField *IodomIField;
    cocos2d::Color3B stillColor;
    cocos2d::Sprite *btt;
    cocos2d::Sprite *btt_clk;
    cocos2d::Sprite *background;
    cocos2d::Color3B buttonColor;
    cocos2d::Color4B textColor;
    cocos2d::Size buttonSize;
    cocos2d::Size inputSize;
    cocos2d::MenuItemSprite *createButton(cocos2d::Sprite *still,cocos2d::ui::TextField *textField,const char *txt,const cocos2d::ccMenuCallback &callback);
    void setVelMax ();
    void setVelMin ();
    void setPodomD ();
    void setIodomD ();
    void setPodomI ();
    void setIodomI ();
};

#endif /* Configuracion_hpp */
