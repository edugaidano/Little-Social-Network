#include "users/handlers.h"

int handlerLoginRequest(LOG_T& logger, StorageController& storage, SOCKET_T& sock, PACKAGE_T* pkg) {
    LOG_DEBUG(logger, "Start handlerLoginRequest");
    char* username = (char*)getItem(pkg);

    ID_T userId = storage.findUser(username);
    free(username);
    PACKAGE_T* pkgReply = createPackage(LOGIN_REPLY);
    if (userId != 0) {
        addItem(pkgReply, (void*)"OK", 3);
    } else {
        addItem(pkgReply, (void*)"Not OK", 7);
    }
    int retVal = sendPackage(logger, sock, pkgReply);
    freePackage(pkgReply);
    return retVal;
}