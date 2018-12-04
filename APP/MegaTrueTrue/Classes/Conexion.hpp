//
//  Conexion.hpp
//  MegaTrueTrue
//
//  Created by Juan Casado Ballesteros on 9/8/18.
//

#ifndef Conexion_hpp
#define Conexion_hpp

#define PORT 5003
#define IP "192.168.1.1"

#include <signal.h>

#include "Hilo.hpp"
#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <unistd.h>
#include <iostream>
#include <arpa/inet.h>

class Conexion {
public:
    Conexion(int sock);
    Conexion();
    ~Conexion();
    void send(char toSend);
    void sendVel(char vel_d, char vel_i);
    bool isConnected ();
private:
    int sock;
    bool connected;
};

#endif /* Conexion_hpp */
