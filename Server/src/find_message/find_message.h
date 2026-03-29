#ifndef FIND_MESSAGE_H
#define FIND_MESSAGE_H

#include "../server_storage/server_storage.h"

// on utils folder
#include "communication/communication.h"

int findMessage(LOG_T& logger, PACKAGE_T* requestPkg, SOCKET socket, UserIndex index);

#endif //FIND_MESSAGE_H