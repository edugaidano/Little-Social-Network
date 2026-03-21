#ifndef USER_MANAGER_H
#define USER_MANAGER_H

#include "../check_login_register/check_login_register.h"

// on utils folder
#include "communication/communication.h"

struct ThreadData {
    SOCKET clientSocket;
    LOG_T* logger;
};

void* userManager(void* usrSock);

#endif
