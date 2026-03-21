#include "check_login_register.h"

int checkLogin(LOG_T& logger, PACKAGE_T* loginPkg, SOCKET socket) {
    char* username = (char*)getItem(loginPkg);
    // Check if the username exist
    bool exist = true;
    PACKAGE_T* pkg = createPackage(LOGIN_REPLY);
    if (exist) {
        addItem(pkg, (void*)"OK", 3);
    } else {
        addItem(pkg, (void*)"Not OK", 7);
    }
    int retVal = sendPackage(logger, socket, pkg);
    freePackage(pkg);
    return retVal;
}

int checkRegister(LOG_T& logger, PACKAGE_T* registerPkg, SOCKET socket) {
    char* username = (char*)getItem(registerPkg);
    // Check if the username exist
    bool exist = false;
    PACKAGE_T* pkg = createPackage(REGISTER_REPLY);
    if (!exist) {
        addItem(pkg, (void*)"OK", 3);
    } else {
        addItem(pkg, (void*)"Not OK", 7);
    }
    int retVal = sendPackage(logger, socket, pkg);
    freePackage(pkg);
    return retVal;
}