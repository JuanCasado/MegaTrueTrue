//
//  Libertad.cpp
//  MegaTrueTrue
//
//  Created by Juan Casado Ballesteros on 9/8/18.
//

#include "Libertad.hpp"

USING_NS_CC;

Libertad::Libertad(Conexion *conexion){
    this->conexion = conexion;
}

Libertad* Libertad::create(Conexion *conexion){
    Libertad *libertad = new(std::nothrow) Libertad(conexion);
    if (libertad && libertad->init()){
        libertad->autorelease();
        return libertad;
    }
    else{
        delete libertad;
        libertad = NULL;
        return NULL;
    }
}

bool Libertad::init(){
    if ( !Scene::init() ){
        return false;
    }
    auto button = ui::Button::create("back.png", "back_clk.png", "back_clk.png");
    if (button == nullptr){
        return false;
    }
    auto circle = Sprite::create("circle.png");
    if (circle == nullptr){
        return false;
    }
    auto title = Label::createWithTTF("Libertad", "fonts/cafe.ttf", 50);
    if (title == nullptr){
        return false;
    }
    speed_l = Label::createWithTTF("Speed: 0", "fonts/cafe.ttf", 20);
    if (speed_l == nullptr){
        return false;
    }
    turn_l = Label::createWithTTF("Turn: 0", "fonts/cafe.ttf", 20);
    if (speed_l == nullptr){
        return false;
    }
    isTouching = false;
    speed = 0;
    turn = 0;
    auto screen = Director::getInstance()->getSafeAreaRect().size;
    center = Vec2(screen.width*0.5, screen.height*0.5);
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
    
    title->setColor(Color3B(0, 0, 0));
    title->setPosition(Vec2(screen.width*0.5, screen.height*0.85));
    this->addChild(title);
    
    speed_l->setColor(Color3B(0, 0, 0));
    speed_l->setPosition(Vec2(screen.width*0.5, screen.height*0.55));
    this->addChild(speed_l);
    
    turn_l->setColor(Color3B(0, 0, 0));
    turn_l->setPosition(Vec2(screen.width*0.5, screen.height*0.45));
    this->addChild(turn_l);
    
    circle->setPosition(Vec2(screen.width*0.5,screen.height*0.5));
    this->addChild(circle);
    
    auto listener1 = EventListenerTouchOneByOne::create();
    listener1->onTouchBegan = [=](Touch* touch, Event* event){
        this->isTouching = true;
        this->lastTouch = touch->getLocation();
        return true;
    };
    listener1->onTouchMoved = [=](Touch* touch, Event* event){
        this->isTouching = true;
        this->lastTouch = touch->getLocation();
    };
    listener1->onTouchEnded = [=](Touch* touch, Event* event){
        this->isTouching = false;
    };
    _eventDispatcher->addEventListenerWithSceneGraphPriority(listener1, this);
    
    this->scheduleUpdate();
    
    return true;
}

void Libertad::update (float t){
    if (isTouching){
        speed = (lastTouch.y - center.y)*0.5;
        if (speed > 100)
            speed = 100;
        else if (speed < -100)
            speed = -100;
        turn = (lastTouch.x - center.x)*0.5;
        if (turn > 100)
            turn = 100;
        else if (turn < -100)
            turn = -100;
    }else{
        speed = 0;
        turn = 0;
    }
    speed_l->setString("Speed: "+std::to_string(speed));
    turn_l->setString("Turn: "+std::to_string(turn));
}
