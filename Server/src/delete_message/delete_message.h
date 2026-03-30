#ifndef DELETE_MESSAGE_H
#define DELETE_MESSAGE_H

#include <vector>
#include "../server_storage/server_storage.h"

// on utils folder
#include "communication/communication.h"

int deleteMessage(LOG_T& logger, PACKAGE_T* requestPkg, SOCKET socket, UserIndex index);

#endif //DELETE_MESSAGE_H