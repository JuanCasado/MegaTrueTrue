//
//  Basico.cpp
//  MegaTrueTrue
//
//  Created by Juan Casado Ballesteros on 10/30/18.
//

#include "Basico.hpp"

USING_NS_CC;

Basico::Basico(Conexion *conexion, bool state){
    this->conexion = conexion;
    this->state = state;
}

Basico* Basico::create(Conexion *conexion, bool state){
    Basico *basico = new(std::nothrow) Basico(conexion, state);
    if (basico && basico->init()){
        basico->autorelease();
        return basico;
    }
    else{
        delete basico;
        basico = NULL;
        return NULL;
    }
}

bool Basico::init(){
    if ( !Scene::init() ){
        return false;
    }
    button_azul_oscuro = ui::Button::create("button.png", "button_clk.png", "button_clk.png");
    if (button_azul_oscuro == nullptr){
        return false;
    }
    button_azul_claro = ui::Button::create("button.png", "button_clk.png", "button_clk.png");
    if (button_azul_oscuro == nullptr){
        return false;
    }
    button_rojo = ui::Button::create("button.png", "button_clk.png", "button_clk.png");
    if (button_azul_oscuro == nullptr){
        return false;
    }
    button_verde = ui::Button::create("button.png", "button_clk.png", "button_clk.png");
    if (button_azul_oscuro == nullptr){
        return false;
    }
    button_amarillo = ui::Button::create("button.png", "button_clk.png", "button_clk.png");
    if (button_azul_oscuro == nullptr){
        return false;
    }
    button_morado = ui::Button::create("button.png", "button_clk.png", "button_clk.png");
    if (button_azul_oscuro == nullptr){
        return false;
    }
    button_blanco = ui::Button::create("button.png", "button_clk.png", "button_clk.png");
    if (button_azul_oscuro == nullptr){
        return false;
    }
    c1 = ui::Button::create("button.png", "button_clk.png", "button_clk.png");
    if (c1 == nullptr){
        return false;
    }
    c2 = ui::Button::create("button.png", "button_clk.png", "button_clk.png");
    if (c2 == nullptr){
        return false;
    }
    c3 = ui::Button::create("button.png", "button_clk.png", "button_clk.png");
    if (c3 == nullptr){
        return false;
    }
    c4 = ui::Button::create("button.png", "button_clk.png", "button_clk.png");
    if (c4 == nullptr){
        return false;
    }
    c5 = ui::Button::create("button.png", "button_clk.png", "button_clk.png");
    if (c5 == nullptr){
        return false;
    }
    c6 = ui::Button::create("button.png", "button_clk.png", "button_clk.png");
    if (c6 == nullptr){
        return false;
    }
    c7 = ui::Button::create("button.png", "button_clk.png", "button_clk.png");
    if (c7 == nullptr){
        return false;
    }
    c8 = ui::Button::create("button.png", "button_clk.png", "button_clk.png");
    if (c8 == nullptr){
        return false;
    }
    c9 = ui::Button::create("button.png", "button_clk.png", "button_clk.png");
    if (c9 == nullptr){
        return false;
    }
    c10 = ui::Button::create("button.png", "button_clk.png", "button_clk.png");
    if (c10 == nullptr){
        return false;
    }
    c11 = ui::Button::create("button.png", "button_clk.png", "button_clk.png");
    if (c11 == nullptr){
        return false;
    }
    c12 = ui::Button::create("button.png", "button_clk.png", "button_clk.png");
    if (c12 == nullptr){
        return false;
    }
    circle = Sprite::create("truetrue.png");
    if (circle == nullptr){
        return false;
    }
    circle = Sprite::create("circle_DES.png");
    if (circle == nullptr){
        return false;
    }
    if (state){
        title = Label::createWithTTF("Mega True True", "fonts/cafe.ttf", 50);
    }
    else{
        title = Label::createWithTTF("NOT CONNECTED", "fonts/cafe.ttf", 50);
    }
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
    pulse = Sprite::create("truetrue.png");
    if (pulse == nullptr){
        return false;
    }
    auto t1 = Label::createWithTTF("1", "fonts/cafe.ttf", 30);
    if (t1 == nullptr){
        return false;
    }
    auto t2 = Label::createWithTTF("2", "fonts/cafe.ttf", 30);
    if (t2 == nullptr){
        return false;
    }
    auto t3 = Label::createWithTTF("3", "fonts/cafe.ttf", 30);
    if (t3 == nullptr){
        return false;
    }
    auto t4 = Label::createWithTTF("4", "fonts/cafe.ttf", 30);
    if (t4 == nullptr){
        return false;
    }
    auto t5 = Label::createWithTTF("5", "fonts/cafe.ttf", 30);
    if (t5 == nullptr){
        return false;
    }
    auto t6 = Label::createWithTTF("6", "fonts/cafe.ttf", 30);
    if (t6 == nullptr){
        return false;
    }
    auto t7 = Label::createWithTTF("7", "fonts/cafe.ttf", 30);
    if (t7 == nullptr){
        return false;
    }
    auto t8 = Label::createWithTTF("8", "fonts/cafe.ttf", 30);
    if (t8 == nullptr){
        return false;
    }
    auto t9 = Label::createWithTTF("9", "fonts/cafe.ttf", 30);
    if (t9 == nullptr){
        return false;
    }
    auto t10 = Label::createWithTTF("10", "fonts/cafe.ttf", 30);
    if (t10 == nullptr){
        return false;
    }
    auto t11 = Label::createWithTTF("11", "fonts/cafe.ttf", 30);
    if (t11 == nullptr){
        return false;
    }
    auto t12 = Label::createWithTTF("12", "fonts/cafe.ttf", 30);
    if (t12 == nullptr){
        return false;
    }
    isTouching = false;
    speed = 0;
    turn = 0;
    count = 0;
    speed_a = 0;
    turn_a = 0;
    count_a = 0;
    auto screen = Director::getInstance()->getSafeAreaRect().size;
    auto center = Vec2(screen.width*0.5, screen.height*0.5);
    button_azul_oscuro->addTouchEventListener([&](Ref* sender, ui::Widget::TouchEventType type){
        switch (type){
            case ui::Widget::TouchEventType::ENDED:
                conexion->send('O');
                circle->setColor(azul_oscuro);
                pulse->setColor(azul_oscuro);
                break;
            default:
                break;
        }
    });
    button_azul_oscuro->setColor(azul_oscuro);
    this->addChild(button_azul_oscuro);
    button_azul_claro->addTouchEventListener([&](Ref* sender, ui::Widget::TouchEventType type){
        switch (type){
            case ui::Widget::TouchEventType::ENDED:
                conexion->send('C');
                circle->setColor(azul_claro);
                pulse->setColor(azul_claro);
                break;
            default:
                break;
        }
    });
    button_azul_claro->setColor(azul_claro);
    this->addChild(button_azul_claro);
    button_rojo->addTouchEventListener([&](Ref* sender, ui::Widget::TouchEventType type){
        switch (type){
            case ui::Widget::TouchEventType::ENDED:
                conexion->send('R');
                circle->setColor(rojo);
                pulse->setColor(rojo);
                break;
            default:
                break;
        }
    });
    button_rojo->setColor(rojo);
    this->addChild(button_rojo);
    button_verde->addTouchEventListener([&](Ref* sender, ui::Widget::TouchEventType type){
        switch (type){
            case ui::Widget::TouchEventType::ENDED:
                conexion->send('V');
                circle->setColor(verde);
                pulse->setColor(verde);
                break;
            default:
                break;
        }
    });
    button_verde->setColor(verde);
    this->addChild(button_verde);
    
    button_morado->addTouchEventListener([&](Ref* sender, ui::Widget::TouchEventType type){
        switch (type){
            case ui::Widget::TouchEventType::ENDED:
                conexion->send('M');
                circle->setColor(morado);
                pulse->setColor(morado);
                break;
            default:
                break;
        }
    });
    button_morado->setColor(morado);
    this->addChild(button_morado);
    button_amarillo->addTouchEventListener([&](Ref* sender, ui::Widget::TouchEventType type){
        switch (type){
            case ui::Widget::TouchEventType::ENDED:
                conexion->send('A');
                circle->setColor(amarillo);
                pulse->setColor(amarillo);
                break;
            default:
                break;
        }
    });
    button_amarillo->setColor(amarillo);
    this->addChild(button_amarillo);
    button_blanco->addTouchEventListener([&](Ref* sender, ui::Widget::TouchEventType type){
        switch (type){
            case ui::Widget::TouchEventType::ENDED:
                conexion->send('B');
                circle->setColor(blanco);
                pulse->setColor(blanco);
                break;
            default:
                break;
        }
    });
    button_blanco->setColor(blanco);
    this->addChild(button_blanco);
    c1->addTouchEventListener([&](Ref* sender, ui::Widget::TouchEventType type){
        switch (type){
            case ui::Widget::TouchEventType::ENDED:
                conexion->send('1');
                break;
            default:
                break;
        }
    });
    c1->setColor(music);
    t1->setAnchorPoint(Vec2(0.5, 0.5));
    t1->setPosition(c1->getContentSize().width/2, c1->getContentSize().height/2);
    c1->addChild(t1);
    this->addChild(c1);
    c2->addTouchEventListener([&](Ref* sender, ui::Widget::TouchEventType type){
        switch (type){
            case ui::Widget::TouchEventType::ENDED:
                conexion->send('2');
                break;
            default:
                break;
        }
    });
    c2->setColor(music);
    t2->setAnchorPoint(Vec2(0.5, 0.5));
    t2->setPosition(c2->getContentSize().width/2, c2->getContentSize().height/2);
    c2->addChild(t2);
    this->addChild(c2);
    c3->addTouchEventListener([&](Ref* sender, ui::Widget::TouchEventType type){
        switch (type){
            case ui::Widget::TouchEventType::ENDED:
                conexion->send('3');
                break;
            default:
                break;
        }
    });
    c3->setColor(music);
    t3->setAnchorPoint(Vec2(0.5, 0.5));
    t3->setPosition(c3->getContentSize().width/2, c3->getContentSize().height/2);
    c3->addChild(t3);
    this->addChild(c3);
    c4->addTouchEventListener([&](Ref* sender, ui::Widget::TouchEventType type){
        switch (type){
            case ui::Widget::TouchEventType::ENDED:
                conexion->send('4');
                break;
            default:
                break;
        }
    });
    c4->setColor(music);
    t4->setAnchorPoint(Vec2(0.5, 0.5));
    t4->setPosition(c4->getContentSize().width/2, c4->getContentSize().height/2);
    c4->addChild(t4);
    this->addChild(c4);
    c5->addTouchEventListener([&](Ref* sender, ui::Widget::TouchEventType type){
        switch (type){
            case ui::Widget::TouchEventType::ENDED:
                conexion->send('5');
                break;
            default:
                break;
        }
    });
    c5->setColor(music);
    t5->setAnchorPoint(Vec2(0.5, 0.5));
    t5->setPosition(c5->getContentSize().width/2, c5->getContentSize().height/2);
    c5->addChild(t5);
    this->addChild(c5);
    c6->addTouchEventListener([&](Ref* sender, ui::Widget::TouchEventType type){
        switch (type){
            case ui::Widget::TouchEventType::ENDED:
                conexion->send('6');
                break;
            default:
                break;
        }
    });
    c6->setColor(music);
    t6->setAnchorPoint(Vec2(0.5, 0.5));
    t6->setPosition(c6->getContentSize().width/2, c6->getContentSize().height/2);
    c6->addChild(t6);
    this->addChild(c6);
    c7->addTouchEventListener([&](Ref* sender, ui::Widget::TouchEventType type){
        switch (type){
            case ui::Widget::TouchEventType::ENDED:
                conexion->send('7');
                break;
            default:
                break;
        }
    });
    c7->setColor(music);
    t7->setAnchorPoint(Vec2(0.5, 0.5));
    t7->setPosition(c7->getContentSize().width/2, c7->getContentSize().height/2);
    c7->addChild(t7);
    this->addChild(c7);
    c8->addTouchEventListener([&](Ref* sender, ui::Widget::TouchEventType type){
        switch (type){
            case ui::Widget::TouchEventType::ENDED:
                conexion->send('8');
                break;
            default:
                break;
        }
    });
    c8->setColor(music);
    t8->setAnchorPoint(Vec2(0.5, 0.5));
    t8->setPosition(c8->getContentSize().width/2, c8->getContentSize().height/2);
    c8->addChild(t8);
    this->addChild(c8);
    c9->addTouchEventListener([&](Ref* sender, ui::Widget::TouchEventType type){
        switch (type){
            case ui::Widget::TouchEventType::ENDED:
                conexion->send('9');
                break;
            default:
                break;
        }
    });
    c9->setColor(music);
    t9->setAnchorPoint(Vec2(0.5, 0.5));
    t9->setPosition(c9->getContentSize().width/2, c9->getContentSize().height/2);
    c9->addChild(t9);
    this->addChild(c9);
    c10->addTouchEventListener([&](Ref* sender, ui::Widget::TouchEventType type){
        switch (type){
            case ui::Widget::TouchEventType::ENDED:
                conexion->send('<');
                break;
            default:
                break;
        }
    });
    c10->setColor(music);
    t10->setAnchorPoint(Vec2(0.5, 0.5));
    t10->setPosition(c10->getContentSize().width/2, c10->getContentSize().height/2);
    c10->addChild(t10);
    this->addChild(c10);
    c11->addTouchEventListener([&](Ref* sender, ui::Widget::TouchEventType type){
        switch (type){
            case ui::Widget::TouchEventType::ENDED:
                conexion->send('>');
                break;
            default:
                break;
        }
    });
    c11->setColor(music);
    t11->setAnchorPoint(Vec2(0.5, 0.5));
    t11->setPosition(c11->getContentSize().width/2, c11->getContentSize().height/2);
    c11->addChild(t11);
    this->addChild(c11);
    c12->addTouchEventListener([&](Ref* sender, ui::Widget::TouchEventType type){
        switch (type){
            case ui::Widget::TouchEventType::ENDED:
                conexion->send('*');
                break;
            default:
                break;
        }
    });
    c12->setColor(music);
    t12->setAnchorPoint(Vec2(0.5, 0.5));
    t12->setPosition(c12->getContentSize().width/2, c12->getContentSize().height/2);
    c12->addChild(t12);
    this->addChild(c12);
    
    this->addChild(title);
    
    circle->setColor(azul_oscuro);
    this->addChild(circle);
    
    speed_l->setPosition(Vec2(circle->getContentSize().width*0.5, circle->getContentSize().height*0.8));
    circle->addChild(speed_l);
    
    turn_l->setPosition(Vec2(circle->getContentSize().width*0.5, circle->getContentSize().height*0.2));
    circle->addChild(turn_l);
    
    pulse->setPosition(Vec2(screen.width*0.5,screen.height*0.5));
    pulse->setColor(azul_oscuro);
    this->addChild(pulse);
    
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
    if (AppDelegate::getScreenOrientation()){
        setLandscape();
    } else {
        setPortrait();
    }
    
    this->scheduleUpdate();
    
    return true;
}

void Basico::update (float t){
    auto screen = Director::getInstance()->getSafeAreaRect().size;
    Vec2 center;
    float factor;
    if (AppDelegate::getScreenOrientation()){
        setLandscape();
        center = Vec2(screen.width*0.75, screen.height*0.5);
        factor = 0.65;
    } else {
        setPortrait();
        center = Vec2(screen.width*0.5, screen.height*0.5);
        factor = 0.5;
    }
    if (isTouching){
        speed = (lastTouch.y - center.y)*factor;
        turn = (lastTouch.x - center.x)*factor;
        if ((speed > 100) || (speed < -100) || (turn > 100) || (turn < -100)){
            speed = 0;
            turn = 0;
        }else{
            pulse->setPositionX(lastTouch.x);
            pulse->setPositionY(lastTouch.y);
        }
        
    }else{
        speed = 0;
        turn = 0;
        pulse->setPosition(center);
    }
    speed_l->setString("Speed: "+std::to_string(speed));
    turn_l->setString("Turn: "+std::to_string(turn));
    if (count < 60){
        count = 0;
        if ((speed_a != speed) || (turn_a != turn) || (count_a > 20)){
            conexion->sendVel((char)(speed+100),(char)(turn+100));
            speed_a = speed;
            turn_a = turn;
            count_a = 0;
        }else{
            count_a ++;
        }
    }else{
        count ++;
    }
}

void Basico::setPortrait(){
    auto screen = Director::getInstance()->getSafeAreaRect().size;
    button_azul_oscuro->setPosition(Vec2(screen.width*1/9, screen.height*0.16));
    button_azul_claro->setPosition(Vec2(screen.width*2/8, screen.height*0.16));
    button_rojo->setPosition(Vec2(screen.width*6/8, screen.height*0.16));
    button_verde->setPosition(Vec2(screen.width*4/8, screen.height*0.16));
    button_morado->setPosition(Vec2(screen.width*5/8, screen.height*0.16));
    button_amarillo->setPosition(Vec2(screen.width*3/8, screen.height*0.16));
    button_blanco->setPosition(Vec2(screen.width*7/8, screen.height*0.16));
    c1->setPosition(Vec2(screen.width/7, screen.height*0.09));
    c2->setPosition(Vec2(screen.width*2/7, screen.height*0.09));
    c3->setPosition(Vec2(screen.width*3/7, screen.height*0.09));
    c4->setPosition(Vec2(screen.width*4/7, screen.height*0.09));
    c5->setPosition(Vec2(screen.width*5/7, screen.height*0.09));
    c6->setPosition(Vec2(screen.width*6/7, screen.height*0.09));
    c7->setPosition(Vec2(screen.width/7, screen.height*0.03));
    c8->setPosition(Vec2(screen.width*2/7, screen.height*0.03));
    c9->setPosition(Vec2(screen.width*3/7, screen.height*0.03));
    c10->setPosition(Vec2(screen.width*4/7, screen.height*0.03));
    c11->setPosition(Vec2(screen.width*5/7, screen.height*0.03));
    c12->setPosition(Vec2(screen.width*6/7, screen.height*0.03));
    circle->setPosition(Vec2(screen.width*0.5,screen.height*0.5));
    title->setPosition(Vec2(screen.width*0.5, screen.height*0.85));
}
void Basico::setLandscape(){
    auto screen = Director::getInstance()->getSafeAreaRect().size;
    button_azul_oscuro->setPosition(Vec2(screen.width*0.5*1/9, screen.height*0.3));
    button_azul_claro->setPosition(Vec2(screen.width*0.5*2/8, screen.height*0.3));
    button_rojo->setPosition(Vec2(screen.width*0.5*6/8, screen.height*0.3));
    button_verde->setPosition(Vec2(screen.width*0.5*4/8, screen.height*0.3));
    button_morado->setPosition(Vec2(screen.width*0.5*5/8, screen.height*0.3));
    button_amarillo->setPosition(Vec2(screen.width*0.5*3/8, screen.height*0.3));
    button_blanco->setPosition(Vec2(screen.width*0.5*7/8, screen.height*0.3));
    c1->setPosition(Vec2(screen.width*0.5/7, screen.height*0.2));
    c2->setPosition(Vec2(screen.width*0.5*2/7, screen.height*0.2));
    c3->setPosition(Vec2(screen.width*0.5*3/7, screen.height*0.2));
    c4->setPosition(Vec2(screen.width*0.5*4/7, screen.height*0.2));
    c5->setPosition(Vec2(screen.width*0.5*5/7, screen.height*0.2));
    c6->setPosition(Vec2(screen.width*0.5*6/7, screen.height*0.2));
    c7->setPosition(Vec2(screen.width*0.5/7, screen.height*0.1));
    c8->setPosition(Vec2(screen.width*0.5*2/7, screen.height*0.1));
    c9->setPosition(Vec2(screen.width*0.5*3/7, screen.height*0.1));
    c10->setPosition(Vec2(screen.width*0.5*4/7, screen.height*0.1));
    c11->setPosition(Vec2(screen.width*0.5*5/7, screen.height*0.1));
    c12->setPosition(Vec2(screen.width*0.5*6/7, screen.height*0.1));
    circle->setPosition(Vec2(screen.width*0.75,screen.height*0.5));
    title->setPosition(Vec2(screen.width*0.5*0.5, screen.height*0.8));
}
