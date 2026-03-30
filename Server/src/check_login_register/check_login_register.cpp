#include "check_login_register.h"

int checkLogin(LOG_T& logger, PACKAGE_T* loginPkg, SOCKET socket, UserIndex index) {
    char* username = (char*)getItem(loginPkg);
    ID_T userId = index.findUser(username);
    free(username);
    PACKAGE_T* pkg = createPackage(LOGIN_REPLY);
    if (userId != 0) {
        addItem(pkg, (void*)"OK", 3);
    } else {
        addItem(pkg, (void*)"Not OK", 7);
    }
    int retVal = sendPackage(logger, socket, pkg);
    freePackage(pkg);
    return retVal;
}

int checkRegister(LOG_T& logger, PACKAGE_T* registerPkg, SOCKET socket, UserIndex index) {
    char* username = (char*)getItem(registerPkg);
    ID_T userId = index.createUser(username);
    free(username);
    PACKAGE_T* pkg = createPackage(REGISTER_REPLY);
    if (userId != 0) {
        addItem(pkg, (void*)"OK", 3);
    } else {
        addItem(pkg, (void*)"Not OK", 7);
    }
    int retVal = sendPackage(logger, socket, pkg);
    freePackage(pkg);
    return retVal;
}