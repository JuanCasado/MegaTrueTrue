//
//  Configuracion.cpp
//  MegaTrueTrue
//
//  Created by Juan Casado Ballesteros on 9/8/18.
//

#include "Configuracion.hpp"

USING_NS_CC;

Configuracion::Configuracion(Conexion *conexion){
    this->conexion = conexion;
}

Configuracion* Configuracion::create(Conexion *conexion){
    Configuracion *configuracion = new(std::nothrow) Configuracion(conexion);
    if (configuracion && configuracion->init()){
        configuracion->autorelease();
        return configuracion;
    }
    else{
        delete configuracion;
        configuracion = NULL;
        return NULL;
    }
}

bool Configuracion::init(){
    if ( !Scene::init() ){
        return false;
    }
    btt = Sprite::create("btt.png");
    if (btt == nullptr){
        return false;
    }
    btt_clk = Sprite::create("btt_clk.png");
    if (btt_clk == nullptr){
        return false;
    }
    background = Sprite::create("WhiteRect.png");
    if (btt_clk == nullptr){
        return false;
    }
    auto title = Label::createWithTTF("Configuración", "fonts/cafe.ttf", 50);
    if (title == nullptr){
        return false;
    }
    auto button = ui::Button::create("back.png", "back_clk.png", "back_clk.png");
    if (button == nullptr){
        return false;
    }
    auto save = ui::Button::create("btt.png", "btt_clk.png", "btt_clk.png");
    if (save == nullptr){
        return false;
    }
    auto screen = Director::getInstance()->getSafeAreaRect().size;
    button->setPosition(Vec2(screen.width*0.5, screen.height*0.13));
    button->addTouchEventListener([&](Ref* sender, ui::Widget::TouchEventType type){
        switch (type){
            case ui::Widget::TouchEventType::ENDED:
                if (conexion->go(Conexion::To::MainMenu)){
                    auto director = Director::getInstance();
                    MainMenu *mainMenu = MainMenu::create(conexion);
                    if (mainMenu!=nullptr){
                        director->replaceScene(mainMenu);
                    }
                }
                break;
            default:
                break;
        }
    });
    this->addChild(button);
    
    title->setPosition(Vec2(screen.width*0.5, screen.height*0.85));
    title->setColor(Color3B(0, 0, 0));
    this->addChild(title);
    
    buttonSize = Size(screen.width*0.3, screen.height*0.06);
    inputSize = Size(screen.width*0.45, screen.height*0.05);
    buttonColor = Color3B(240, 240, 240);
    stillColor = Color3B(250, 250, 250);
    textColor = Color4B(20, 40, 20, 255);
    
    Vector<MenuItem*> menuItems;
    menuItems.pushBack(createButton(velMaxBackgroudStill, velMaxField, "Set VEL-MAX", CC_CALLBACK_0(Configuracion::setVelMax, this)));
    menuItems.pushBack(createButton(velMinBackgroudStill, velMinField, "Set VEL-MIN", CC_CALLBACK_0(Configuracion::setVelMin, this)));
    menuItems.pushBack(createButton(PodomDBackgroudStill, PodomDField, "Set PodomD", CC_CALLBACK_0(Configuracion::setPodomD, this)));
    menuItems.pushBack(createButton(IodomDBackgroudStill, IodomDField, "Set IodomD", CC_CALLBACK_0(Configuracion::setIodomD, this)));
    menuItems.pushBack(createButton(PodomIBackgroudStill, PodomIField, "Set PodomI", CC_CALLBACK_0(Configuracion::setPodomI, this)));
    menuItems.pushBack(createButton(IodomIBackgroudStill, IodomIField, "Set IodomI", CC_CALLBACK_0(Configuracion::setIodomI, this)));
    auto buttonHolder = Menu::createWithArray(menuItems);
    buttonHolder->alignItemsVerticallyWithPadding(15);
    buttonHolder->setPosition(Vec2(screen.width*0.6, screen.height*0.54));
    this->addChild(buttonHolder);
    
    save->setPosition(Vec2(screen.width*0.5,screen.height*0.25));
    save->setTitleText("SAVE");
    save->setTitleFontName("fonts/cafe.ttf");
    save->setTitleFontSize(20);
    save->addTouchEventListener([&](Ref* sender, ui::Widget::TouchEventType type){
        switch (type){
            case ui::Widget::TouchEventType::ENDED:
                
                break;
            default:
                break;
        }
    });
    this->addChild(save);
    
    return true;
}

void Configuracion::setVelMax(){
    
}
void Configuracion::setVelMin(){
    
}
void Configuracion::setPodomD(){
    
}
void Configuracion::setIodomD(){
    
}
void Configuracion::setPodomI(){
    
}
void Configuracion::setIodomI(){
    
}

cocos2d::MenuItemSprite *Configuracion::createButton(cocos2d::Sprite *backgroundStill,cocos2d::ui::TextField *textField,const char *txt,const cocos2d::ccMenuCallback &callback){
    auto bttStill = Sprite::createWithTexture(btt->getTexture());
    bttStill->setContentSize(buttonSize);
    auto bttClicked = Sprite::createWithTexture(btt_clk->getTexture());
    bttClicked->setContentSize(buttonSize);
    auto btt = MenuItemSprite::create(bttStill, bttClicked, callback);
    auto label = Label::createWithTTF(txt, "fonts/cafe.ttf", 23);
    label->setPosition(bttStill->getContentSize().width/2, bttStill->getContentSize().height/2);
    label->setColor(buttonColor);
    btt->addChild(label);
    backgroundStill = Sprite::createWithTexture(background->getTexture());
    backgroundStill->setContentSize(inputSize);
    backgroundStill->setColor(stillColor);
    textField = ui::TextField::create("0000","fonts/Marker Felt.ttf",16);
    textField->setCursorEnabled(true);
    textField->setTextColor(textColor);
    textField->setMaxLength(15);
    textField->setPosition(Vec2(inputSize.width*0.5, inputSize.height*0.5));
    textField->setTextHorizontalAlignment(TextHAlignment::LEFT);
    backgroundStill->addChild(textField);
    btt->setAnchorPoint(Vec2(0, 0.5));
    backgroundStill->setAnchorPoint(Vec2(1, 0.5));
    backgroundStill->setPosition(Vec2(-buttonSize.width*0.25, buttonSize.height*0.5));
    btt->addChild(backgroundStill);
    
    return btt;
}
