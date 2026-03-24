#ifndef SEND_MESSAGE_H
#define SEND_MESSAGE_H

// on utils folder
#include "communication/communication.h"

int sendMessage(LOG_T& logger, PACKAGE_T* messagePkg, SOCKET socket);

#endif //SEND_MESSAGE_H