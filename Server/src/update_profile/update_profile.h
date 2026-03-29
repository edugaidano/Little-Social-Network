#ifndef UPDATE_PROFILE_H
#define UPDATE_PROFILE_H

#include "../server_storage/server_storage.h"

// on utils folder
#include "communication/communication.h"

int updateProfile(LOG_T& logger, PACKAGE_T* updatePkg, SOCKET socket, UserIndex index);

#endif //UPDATE_PROFILE_H