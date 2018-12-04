//
//  Odometria.hpp
//  MegaTrueTrue
//
//  Created by Juan Casado Ballesteros on 9/8/18.
//

#ifndef Odometria_hpp
#define Odometria_hpp

#include "Conexion.hpp"
#include "ui/CocosGUI.h"
#include "MainMenu.hpp"
#include <vector>

#define MAX_DATA 50

class Odometria : public cocos2d::Scene{
public:
    static Odometria *create(Conexion *conexion);
private:
    Odometria (Conexion *conexion);
    virtual bool init () override;
    Conexion *conexion;
    std::vector <cocos2d::Sprite*> buff;
    std::vector <char> buff_c;
    int read_index;
    int write_index;
    cocos2d::ui::Button *go;
    bool simulating;
    void update (float t) override;
    cocos2d::Sprite *display;
    cocos2d::ProgressTimer *timer;
    void createSprites();
    void clearSprites();
};

#endif /* Odometria_hpp */
