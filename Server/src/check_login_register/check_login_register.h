#ifndef CHECK_LOGIN_REGISTER_H
#define CHECK_LOGIN_REGISTER_H

#include "../server_storage/server_storage.h"

// on utils folder
#include "communication/communication.h"

int checkLogin(LOG_T& logger, PACKAGE_T* loginPkg, SOCKET socket, UserIndex index);
int checkRegister(LOG_T& logger, PACKAGE_T* loginPkg, SOCKET socket, UserIndex index);

#endif // CHECK_LOGIN_REGISTER_H