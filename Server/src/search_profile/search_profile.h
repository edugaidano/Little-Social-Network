#ifndef SEARCH_PROFILE_H
#define SEARCH_PROFILE_H

#include "../server_storage/server_storage.h"

// on utils folder
#include "communication/communication.h"

int searchProfile(LOG_T& logger, PACKAGE_T* searchPkg, SOCKET socket, UserIndex index);

#endif //SEARCH_PROFILE_H