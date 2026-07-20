#ifndef MAKE_CONNECTION_H
#define MAKE_CONNECTION_H

#include "communication/communication.h"
#include <WS2tcpip.h>

SOCKET make_connection(LOG_T& logger, const char *ip, const char *port);

#endif