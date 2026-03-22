#ifndef _CONNECT_SERVER_H
#define _CONNECT_SERVER_H

#include <cstdio>
#include <iostream>
#include <WinSock2.h>
#include <WS2tcpip.h>

#include "../dialog/dialog.h"

#include "logs/logs.h" // on utils folder

SOCKET connectToServer(LOG_T &logger, const char *ip,const char *port);

#endif