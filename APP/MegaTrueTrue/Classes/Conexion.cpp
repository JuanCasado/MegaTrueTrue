//
//  Conexion.cpp
//  MegaTrueTrue
//
//  Created by Juan Casado Ballesteros on 9/8/18.
//

#include "Conexion.hpp"

Conexion::Conexion (int sock){
    connected = true;
    this->sock = sock;
}

Conexion::Conexion (){
    connected = false;
    struct sockaddr_in server;
    server.sin_port = htons(PORT);
    server.sin_addr.s_addr = inet_addr(IP);
    server.sin_family = AF_INET;
    bzero(&(server.sin_zero),8);
    if ((sock = socket(AF_INET, SOCK_STREAM, 0))>=0){
        if(connect(sock, (struct sockaddr *)&server, sizeof(struct sockaddr))>=0){
            connected = true;
            struct timeval tv;
            //int optval = 1;
            tv.tv_sec = 10;
            tv.tv_usec = 0;
            setsockopt(sock, SOL_SOCKET, SO_RCVTIMEO, (const char*)&tv, sizeof tv);
            //setsockopt(sock,SOL_SOCKET,SO_NOSIGPIPE,&optval,socklen_t(sizeof(optval)));
            signal(SIGPIPE, SIG_IGN);
        }else{
            close(sock);
        }
    }else{
        close(sock);
    }
}

Conexion::~Conexion(){
    connected = false;
    close(sock);
}

void Conexion::send(char data){
    if (connected){
        char toSend [2] = {'0','\r'};
        toSend [0] = data;
        if (write(sock, &toSend, sizeof(toSend)) < 0){
            connected = false;
            close(sock);
        }
    }
}

void Conexion::sendVel(char vel_d, char vel_i){
    if (connected){
        char toSend [4] = {'H','0', '0','\r'};
        toSend[1] = vel_d;
        toSend[2] = vel_i;
        if (write(sock, &toSend, sizeof(toSend)) < 0){
            connected = false;
            close(sock);
        }
    }
}

bool Conexion::isConnected (){
    return connected;
}
