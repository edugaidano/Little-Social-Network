#ifndef COMMUNICATION_H
#define COMMUNICATION_H

#include <string>
#include <cstdio>
#include <iostream>

#include "logs/logs.h"
#include "serialization/serialization.h"

#ifdef _WIN32
    #include <winsock2.h>

    #pragma comment(lib, "Ws2_32.lib")

    #define SOCKET_T SOCKET
#endif // _WIN32

#ifdef __linux__
    #include <errno.h>
    #include <sys/socket.h>

    #define SOCKET_T int
#endif // __linux__

int sendPackage(LOG_T& logger, SOCKET_T socket, PACKAGE_T* package);
PACKAGE_T* recvPackage(LOG_T& logger, SOCKET_T socket);

#endif // COMMUNICATION_H