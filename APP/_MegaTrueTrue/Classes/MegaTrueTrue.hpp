//
//  MegaTrueTrue.hpp
//  MegaTrueTrue
//
//  Created by Juan Casado Ballesteros on 9/6/18.
//

#ifndef MegaTrueTrue_hpp
#define MegaTrueTrue_hpp

#define PORT 80
#define IP "192.168.1.1"

#include "cocos2d.h"
#include "Hilo.hpp"
#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <unistd.h>
#include <iostream>
#include <arpa/inet.h>
#include <atomic>
#include "Conexion.hpp"
#include "Odometria.hpp"
#include "MainMenu.hpp"
#include "Libertad.hpp"
#include "Basico.hpp"
#include "Configuracion.hpp"

class MegaTrueTrue : public cocos2d::Scene, Hilo{
public:
    static MegaTrueTrue* createScene();
private:
    virtual bool init();
    CREATE_FUNC(MegaTrueTrue);
    void update (float t);
    cocos2d::Label *title;
    float percentage;
    bool direction;
    cocos2d::ProgressTimer *countdownTimer;
    std::atomic_bool buscando;
    int timer;
    
    struct sockaddr_in server;
    int sock;
    ~MegaTrueTrue();
protected:
    virtual void to_do();
    virtual void to_end();
    virtual void to_beguin();
};

#endif /* MegaTrueTrue_hpp */
