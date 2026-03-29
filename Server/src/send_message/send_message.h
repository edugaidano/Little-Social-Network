#ifndef SEND_MESSAGE_H
#define SEND_MESSAGE_H

#include "../server_storage/server_storage.h"

// on utils folder
#include "communication/communication.h"

int sendMessage(LOG_T& logger, PACKAGE_T* messagePkg, SOCKET socket, UserIndex index);

#endif //SEND_MESSAGE_H