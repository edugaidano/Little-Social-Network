#ifndef START_SERVER_H
#define START_SERVER_H

#undef UNICODE
#define WIN32_LEAN_AND_MEAN

#include <windows.h>
#include <winsock2.h>
#include <ws2tcpip.h>
#include <stdlib.h>
#include <stdio.h>

#pragma comment (lib, "Ws2_32.lib")

// on utils folder
#include "logs/logs.h"

SOCKET startServer(LOG_T &logs, std::string& port);

#endif // START_SERVER_H