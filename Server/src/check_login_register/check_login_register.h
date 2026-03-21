#ifndef CHECK_LOGIN_REGISTER_H
#define CHECK_LOGIN_REGISTER_H

// on utils folder
#include "communication/communication.h"

int checkLogin(LOG_T& logger, PACKAGE_T* loginPkg, SOCKET socket);
int checkRegister(LOG_T& logger, PACKAGE_T* loginPkg, SOCKET socket);

#endif // CHECK_LOGIN_REGISTER_H