//
//  Conexion.hpp
//  MegaTrueTrue
//
//  Created by Juan Casado Ballesteros on 9/8/18.
//

#ifndef Conexion_hpp
#define Conexion_hpp

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
#include <vector>

class Conexion : public Hilo {
public:
    enum To {
        Odometria,
        MainMenu,
        Libertad,
        Configuracion,
    };
    Conexion(int sock);
    ~Conexion();
    bool go(Conexion::To to);
    void startOdometry (std::vector<char> buff);
    void send(char toSend);
    void sendVel(char vel_d, char vel_i);
private:
    int sock;
protected:
    virtual void to_do();
    virtual void to_end();
    virtual void to_beguin();
};

#endif /* Conexion_hpp */
