//
//  Odometria.cpp
//  MegaTrueTrue
//
//  Created by Juan Casado Ballesteros on 9/8/18.
//

#include "Odometria.hpp"

USING_NS_CC;

Odometria::Odometria(Conexion *conexion){
    this->conexion = conexion;
}

Odometria* Odometria::create(Conexion *conexion){
    Odometria *odometria = new(std::nothrow) Odometria(conexion);
    if (odometria && odometria->init()){
        odometria->autorelease();
        return odometria;
    }
    else{
        delete odometria;
        odometria = NULL;
        return NULL;
    }
}

bool Odometria::init(){
    if ( !Scene::init() ){
        return false;
    }
    auto button = ui::Button::create("back.png", "back_clk.png", "back_clk.png");
    if (button == nullptr){
        return false;
    }
    auto up = ui::Button::create("up.png", "upf.png", "upf.png");
    if (up == nullptr){
        return false;
    }
    auto right = ui::Button::create("right.png", "rightf.png", "rightf.png");
    if (right == nullptr){
        return false;
    }
    auto left = ui::Button::create("left.png", "leftf.png", "leftf.png");
    if (left == nullptr){
        return false;
    }
    auto down = ui::Button::create("down.png", "downf.png", "downf.png");
    if (down == nullptr){
        return false;
    }
    go = ui::Button::create("go.png", "go_clk.png", "go_clk.png");
    if (go == nullptr){
        return false;
    }
    auto title = Label::createWithTTF("Odometría", "fonts/cafe.ttf", 50);
    if (title == nullptr){
        return false;
    }
    read_index = 0;
    write_index = 0;
    simulating = false;
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
    
    title->setColor(Color3B(0, 0, 0));
    title->setPosition(Vec2(screen.width*0.5, screen.height*0.85));
    this->addChild(title);
    
    up->setPosition(Vec2(screen.width*0.6,screen.height*0.52));
    up->addTouchEventListener([&](Ref* sender, ui::Widget::TouchEventType type){
        switch (type){
            case ui::Widget::TouchEventType::ENDED:
                if (read_index < MAX_DATA && !this->simulating){
                    this->buff[this->read_index]->setTexture("upmf.png");
                    this->read_index++;
                    this->buff_c.push_back('U');
                }
                break;
            default:
                break;
        }
    });
    this->addChild(up);
    down->setPosition(Vec2(screen.width*0.6,screen.height*0.28));
    down->addTouchEventListener([&](Ref* sender, ui::Widget::TouchEventType type){
        switch (type){
            case ui::Widget::TouchEventType::ENDED:
                if (read_index < MAX_DATA && !this->simulating){
                    this->buff[this->read_index]->setTexture("downmf.png");
                    this->read_index++;
                    this->buff_c.push_back('D');
                }
                break;
            default:
                break;
        }
    });
    this->addChild(down);
    right->setPosition(Vec2(screen.width*0.8,screen.height*0.4));
    right->addTouchEventListener([&](Ref* sender, ui::Widget::TouchEventType type){
        switch (type){
            case ui::Widget::TouchEventType::ENDED:
                if (read_index < MAX_DATA && !this->simulating){
                    this->buff[this->read_index]->setTexture("rightmf.png");
                    this->read_index++;
                    this->buff_c.push_back('R');
                }
                break;
            default:
                break;
        }
    });
    this->addChild(right);
    left->setPosition(Vec2(screen.width*0.4,screen.height*0.4));
    left->addTouchEventListener([&](Ref* sender, ui::Widget::TouchEventType type){
        switch (type){
            case ui::Widget::TouchEventType::ENDED:
                if (read_index < MAX_DATA && !this->simulating){
                    this->buff[this->read_index]->setTexture("leftmf.png");
                    this->read_index++;
                    this->buff_c.push_back('L');
                }
                break;
            default:
                break;
        }
    });
    this->addChild(left);
    go->setPosition(Vec2(screen.width*0.6,screen.height*0.4));
    go->setTitleText("GO");
    go->setTitleFontName("fonts/cafe.ttf");
    go->setTitleFontSize(20);
    go->addTouchEventListener([&](Ref* sender, ui::Widget::TouchEventType type){
        switch (type){
            case ui::Widget::TouchEventType::ENDED:
                if (!this->simulating){
                    this->simulating = true;
                    this->go->setTitleText("STOP");
                    this->display->setVisible(true);
                    this->conexion->startOdometry(buff_c);
                    this->scheduleUpdate();
                    this->timer->setPercentage(100);
                }
                break;
            default:
                break;
        }
    });
    this->addChild(go);
    
    createSprites();
    
    display = Sprite::create();
    display->setPosition(Vec2(screen.width*0.6, screen.height*0.7));
    timer = ProgressTimer::create(Sprite::create());
    timer->setType(ProgressTimer::Type::BAR);
    timer->setPosition(Vec2(display->getContentSize().width*0.5, display->getContentSize().height*0.5));
    display->addChild(timer);
    this->addChild(display);
    
    return true;
}

void Odometria::update (float t){
    if (buff_c.size()==0 || write_index > read_index){
        unscheduleUpdate();
        read_index = 0;
        write_index = 0;
        buff_c.clear();
        clearSprites();
        createSprites();
        display->setVisible(false);
        timer->setSprite(Sprite::create());
        this->go->setTitleText("GO");
        this->simulating = false;
    }else{
        if (timer->getPercentage()<100){
            timer->setPercentage(timer->getPercentage()+0.5);
        }else{
            switch (buff_c[write_index]) {
                case 'U':
                    display->setTexture("upf.png");
                    timer->setSprite(Sprite::create("up.png"));
                    timer->setMidpoint(Vec2(0.5, 0));
                    timer->setBarChangeRate(Vec2(0, 1));
                    timer->setPosition(Vec2(display->getContentSize().width*0.5, display->getContentSize().height*0.5));
                    buff[write_index]->setTexture("upm.png");
                    break;
                case 'D':
                    display->setTexture("downf.png");
                    timer->setSprite(Sprite::create("down.png"));
                    timer->setMidpoint(Vec2(0.5, 1));
                    timer->setBarChangeRate(Vec2(0, 1));
                    timer->setPosition(Vec2(display->getContentSize().width*0.5, display->getContentSize().height*0.5));
                    buff[write_index]->setTexture("downm.png");
                    break;
                case 'R':
                    display->setTexture("rightf.png");
                    timer->setSprite(Sprite::create("right.png"));
                    timer->setMidpoint(Vec2(0, 0.5));
                    timer->setBarChangeRate(Vec2(1, 0));
                    timer->setPosition(Vec2(display->getContentSize().width*0.5, display->getContentSize().height*0.5));
                    buff[write_index]->setTexture("rightm.png");
                    break;
                case 'L':
                    display->setTexture("leftf.png");
                    timer->setSprite(Sprite::create("left.png"));
                    timer->setMidpoint(Vec2(1, 0.5));
                    timer->setBarChangeRate(Vec2(1, 0));
                    timer->setPosition(Vec2(display->getContentSize().width*0.5, display->getContentSize().height*0.5));
                    buff[write_index]->setTexture("leftm.png");
                    break;
                default:
                    break;
            }
            timer->setPercentage(0);
            write_index += 1;
        }
    }
}

void Odometria::clearSprites(){
    for (int x = 0; x < 50; x++){
        buff[x]->setVisible(false);
        this->removeChild(buff[x]);
    }
    buff.clear();
}
void Odometria::createSprites(){
    auto screen = Director::getInstance()->getSafeAreaRect().size;
    for (int x = 0; x < 50; x++){
        Sprite *arrow = Sprite::create();
        if (x<25)
            arrow->setPosition(Vec2(screen.width*0.1, screen.height*0.82-screen.height*0.03*x));
        else
            arrow->setPosition(Vec2(screen.width*0.2, screen.height*0.82-screen.height*0.03*(x-25)));
        this->addChild(arrow);
        buff.push_back(arrow);
    }
}
