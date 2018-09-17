//
//  Conexion.cpp
//  MegaTrueTrue
//
//  Created by Juan Casado Ballesteros on 9/8/18.
//

#include "Conexion.hpp"

Conexion::Conexion (int sock){
    this->sock = sock;
}

Conexion::~Conexion(){
    close(sock);
    this->end();
}

void Conexion::to_do(){
    
}
void Conexion::to_end(){
    
}
void Conexion::to_beguin(){
    
}

bool Conexion::go (Conexion::To to){
    char toSend = 'Z';
    char toRecive = '0';
    write(sock, &toSend, sizeof(toSend));
    recv(sock, &toRecive,sizeof(toRecive),0);
    switch (to) {
        case Conexion::To::MainMenu:{
            if (toRecive == 'M'){
                return true;
            }
            break;
        }
        case Conexion::To::Odometria:{
            if (toRecive == 'O'){
                return true;
            }
            break;
        }
        case Conexion::To::Libertad:{
            if (toRecive == 'L'){
                return true;
            }
            break;
        }
        case Conexion::To::Configuracion:{
            if (toRecive == 'C'){
                return true;
            }
            break;
        }
        default:
            return false;
            break;
    }
    return false;
}

void Conexion::startOdometry (std::vector<char> buff){
    
}
