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
    auto truetrue = Sprite::create("truetrue.png");
    if (truetrue == nullptr){
        return false;
    }
    title = Label::createWithTTF("Conectando con MegaTrueTrue", "fonts/cafe.ttf", 35);
    if (title ==  nullptr){
        return false;
    }
    buscando.store(true,std::memory_order_seq_cst);
    this->run();
    auto screen = Director::getInstance()->getSafeAreaRect().size;
    truetrue->setPosition(Vec2(screen.width*0.5, screen.height*0.505));
    truetrue->setColor(Color3B(0,0,200));
    this->addChild(truetrue);
    countdownTimer = ProgressTimer::create(myclock);
    countdownTimer->setType(ProgressTimer::Type::RADIAL);
    countdownTimer->setPercentage(0);
    countdownTimer->setPosition(Vec2(screen.width*0.5, screen.height*0.5));
    this->addChild(countdownTimer);
    percentage = 0;
    direction = true;
    timer = 0;
    
    title->setAnchorPoint(Vec2(0.5, 0.5));
    title->setPosition(screen.width*0.5, screen.height*0.85);
    this->addChild(title);
    
    scheduleUpdate();
    return true;
}

void MegaTrueTrue::update (float t){
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
        this->unscheduleUpdate();
        this->end();
        if (buscando.load(std::memory_order_seq_cst)){
            title->setString("MegaTrueTrue NOT FOUND");
            auto conexion = new Conexion (sock);
            conexion->send('B');
            auto director = Director::getInstance();
            Basico *basico = Basico::create(conexion);
            if (basico!=nullptr){
                director->replaceScene(basico);
            }
        }else{
            title->setString("MegaTrueTrue FOUND");
            auto conexion = new Conexion (sock);
            conexion->send('B');
            auto director = Director::getInstance();
            Basico *basico = Basico::create(conexion);
            if (basico!=nullptr){
                director->replaceScene(basico);
            }
        }
    }
}

void MegaTrueTrue::to_do(){
    if (buscando.load(std::memory_order_seq_cst)){
        if ((sock = socket(AF_INET, SOCK_STREAM, 0))>=0){
            if(connect(sock, (struct sockaddr *)&server, sizeof(struct sockaddr))>=0){
                buscando.store(false,std::memory_order_seq_cst);
                struct timeval tv;
                tv.tv_sec = 15;
                tv.tv_usec = 0;
                setsockopt(sock, SOL_SOCKET, SO_RCVTIMEO, (const char*)&tv, sizeof tv);
                char toSend = 'Z';
                write(sock, &toSend, sizeof(toSend));
            }else{
                close(sock);
            }
        }else{
            close(sock);
        }
    }
}
void MegaTrueTrue::to_end(){
    if (buscando.load(std::memory_order_seq_cst)){
        close(sock);
    }
}
void MegaTrueTrue::to_beguin(){
    server.sin_port = htons(PORT);
    server.sin_addr.s_addr = inet_addr(IP);
    server.sin_family = AF_INET;
    bzero(&(server.sin_zero),8);
}

MegaTrueTrue::~MegaTrueTrue(){
    this->end();
}
