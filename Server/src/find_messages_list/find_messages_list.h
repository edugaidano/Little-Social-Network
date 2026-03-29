#ifndef FIND_MESSAGES_LIST_H
#define FIND_MESSAGES_LIST_H

#include "../server_storage/server_storage.h"

// on utils folder
#include "communication/communication.h"

int findMessagesList(LOG_T& logger, PACKAGE_T* requestPkg, SOCKET socket, UserIndex index);

#endif //FIND_MESSAGES_LIST_H