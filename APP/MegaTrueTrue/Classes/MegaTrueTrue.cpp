//
//  MegaTrueTrue.cpp
//  MegaTrueTrue
//
//  Created by Juan Casado Ballesteros on 9/6/18.
//

#include "MegaTrueTrue.hpp"
USING_NS_CC;

MegaTrueTrue* MegaTrueTrue::createScene(){
    return MegaTrueTrue::create();
}

bool MegaTrueTrue::init(){
    auto myclock = Sprite::create("circle.png");
    if (myclock==nullptr){
        return false;
    }
    truetrue = Sprite::create("truetrue.png");
    if (truetrue == nullptr){
        return false;
    }
    title = Label::createWithTTF("Conectando con MegaTrueTrue", "fonts/cafe.ttf", 35);
    if (title ==  nullptr){
        return false;
    }
    auto screen = Director::getInstance()->getSafeAreaRect().size;
    countdownTimer = ProgressTimer::create(myclock);
    countdownTimer->setType(ProgressTimer::Type::RADIAL);
    countdownTimer->setPercentage(0);
    this->addChild(countdownTimer);
    truetrue->setColor(Color3B(0,0,200));
    this->addChild(truetrue);
    percentage = 0;
    direction = true;
    timer = 0;

    title->setAnchorPoint(Vec2(0.5, 0.5));
    this->addChild(title);
    
    if (AppDelegate::getScreenOrientation()){
        setLandscape();
    } else {
        setPortrait();
    }
    
    scheduleUpdate();
    return true;
}

void MegaTrueTrue::update (float t){
    if (AppDelegate::getScreenOrientation()){
        setLandscape();
    } else {
        setPortrait();
    }
    if (timer < 3){
        if (direction){
            percentage ++;
            countdownTimer->setRotation(((percentage)/100)*360);
        }else{
            percentage --;
            countdownTimer->setRotation(((-percentage*2)/100)*360);
        }
        if ((percentage<=0)||(percentage>=100)){
            direction = !direction;
            timer ++;
        }
        countdownTimer->setPercentage(percentage);
    }else{
        connexion = new Conexion();
        this->unscheduleUpdate();
        if (connexion->isConnected()){
            title->setString("MegaTrueTrue FOUND");
            auto director = Director::getInstance();
            Basico *basico = Basico::create(connexion, true);
            if (basico!=nullptr){
                director->replaceScene(basico);
            }
        }else{
            title->setString("MegaTrueTrue NOT FOUND");
            auto director = Director::getInstance();
            Basico *basico = Basico::create(connexion, false);
            if (basico!=nullptr){
                director->replaceScene(basico);
            }
        }
    }
}

MegaTrueTrue::~MegaTrueTrue(){}

void MegaTrueTrue::setPortrait(){
    auto screen = Director::getInstance()->getSafeAreaRect().size;
    title->setPosition(screen.width*0.5, screen.height*0.85);
    countdownTimer->setPosition(Vec2(screen.width*0.5, screen.height*0.5));
    truetrue->setPosition(Vec2(screen.width*0.5, screen.height*0.505));
}
void MegaTrueTrue::setLandscape(){
    auto screen = Director::getInstance()->getSafeAreaRect().size;
    title->setPosition(screen.width*0.5, screen.height*0.85);
    countdownTimer->setPosition(Vec2(screen.width*0.5, screen.height*0.5));
    truetrue->setPosition(Vec2(screen.width*0.5, screen.height*0.505));
}
