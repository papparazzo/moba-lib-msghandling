/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/*
 * File:   socket.cpp
 * Author: 4paproth
 *
 * Created on 8. Januar 2019, 18:05
 */

#include "socket.h"
#include <cstring>

#include <sys/types.h>
#include <sys/socket.h>
#include <sys/time.h>

#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <unistd.h>

Socket::Socket(const std::string &host, int port) : socket(-1) {
    if(host == "" || port > 64738 || port < 1024) {
        throw SocketException("either host or port is invalid!");
    }
    this->host = host;
    this->port = port;
    init();
}

Socket::~Socket() {
    //sendMsg(Message::MT_CLIENT_CLOSE);
    if (socket != -1) {
        close(socket);
    }
}

void Socket::init() {
    if(socket != -1) {
        close(socket);
    }
    socket = ::socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    if(socket == -1) {
        throw SocketException("socket creation failed");
    }

    struct sockaddr_in host_addr;

    memset(&host_addr, 0, sizeof (host_addr));
    host_addr.sin_family = AF_INET;
    host_addr.sin_port = htons(port);
    host_addr.sin_addr.s_addr = inet_addr(host.c_str());

    if(host_addr.sin_addr.s_addr == INADDR_NONE) {
        struct hostent *hostn;

        hostn = gethostbyname(host.c_str());

        if(hostn == nullptr) {
            throw SocketException("resolving url failed");
        }
        memcpy(
            (char*) &host_addr.sin_addr.s_addr,
            hostn->h_addr_list[0],
            hostn->h_length
        );
    }

    if(::connect(socket, (struct sockaddr*) &host_addr, sizeof (host_addr)) == -1) {
        throw SocketException("connection to host failed");
    }
}
