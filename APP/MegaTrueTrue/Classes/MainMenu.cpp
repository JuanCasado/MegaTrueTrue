//
//  MainMenu.cpp
//  MegaTrueTrue
//
//  Created by Juan Casado Ballesteros on 9/8/18.
//

#include "MainMenu.hpp"

USING_NS_CC;

MainMenu::MainMenu(Conexion *conexion){
    this->conexion = conexion;
}

MainMenu* MainMenu::create(Conexion *conexion){
    MainMenu *mainMenu = new(std::nothrow) MainMenu(conexion);
    if (mainMenu && mainMenu->init()){
        mainMenu->autorelease();
        return mainMenu;
    }
    else{
        delete mainMenu;
        mainMenu = NULL;
        return NULL;
    }
}

bool MainMenu::init(){
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
    auto title = Label::createWithTTF("MegaTrueTrue", "fonts/cafe.ttf", 50);
    if (title == nullptr){
        return false;
    }
    auto screen = Director::getInstance()->getSafeAreaRect().size;
    title->setPosition(Vec2(screen.width*0.5, screen.height*0.85));
    title->setColor(Color3B(0, 0, 0));
    this->addChild(title);
    
    buttonSize = Size(screen.width*0.43, screen.height*0.09);
    buttonColor = Color3B(240, 240, 240);
    
    Vector<MenuItem*> menuItems;
    menuItems.pushBack(createButton("Odometria", CC_CALLBACK_0(MainMenu::odometriaClicked, this)));
    menuItems.pushBack(createButton("Libertad", CC_CALLBACK_0(MainMenu::libertadClicked, this)));
    menuItems.pushBack(createButton("Configuración", CC_CALLBACK_0(MainMenu::configuracionClicked, this)));
    auto buttonHolder = Menu::createWithArray(menuItems);
    buttonHolder->alignItemsVerticallyWithPadding(25);
    buttonHolder->setPosition(Vec2(screen.width*0.5, screen.height*0.45));
    this->addChild(buttonHolder);
    return true;
}

void MainMenu::odometriaClicked (){
    if (conexion->go(Conexion::To::Odometria)){
        auto director = Director::getInstance();
        Odometria *odometria = Odometria::create(conexion);
        if (odometria!=nullptr){
            director->replaceScene(odometria);
        }
    }
}

void MainMenu::libertadClicked (){
    if (conexion->go(Conexion::To::Libertad)){
        auto director = Director::getInstance();
        Libertad *libertad = Libertad::create(conexion);
        if (libertad!=nullptr){
            director->replaceScene(libertad);
        }
    }
}

void MainMenu::configuracionClicked(){
    if (conexion->go(Conexion::To::Configuracion)){
        auto director = Director::getInstance();
        Configuracion *configuracion = Configuracion::create(conexion);
        if (configuracion!=nullptr){
            director->replaceScene(configuracion);
        }
    }
}

MenuItemSprite *MainMenu::createButton(const char *txt,const ccMenuCallback &callback){
    auto still = Sprite::createWithTexture(btt->getTexture());
    still->setContentSize(buttonSize);
    auto clicked = Sprite::createWithTexture(btt_clk->getTexture());
    clicked->setContentSize(buttonSize);
    auto btt = MenuItemSprite::create(still, clicked, callback);
    auto label = Label::createWithTTF(txt, "fonts/cafe.ttf", 25);
    label->setPosition(still->getContentSize().width/2, still->getContentSize().height/2);
    label->setColor(buttonColor);
    btt->addChild(label);
    return btt;
}
