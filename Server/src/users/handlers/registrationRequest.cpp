#include "users/handlers.h"

int handlerRegistrationRequest(LOG_T& logger, StorageController& storage, SOCKET_T& sock, PACKAGE_T* pkg) {
    LOG_DEBUG(logger, "Start handlerRegistrationRequest");
    char* username = (char*)getItem(pkg);
    ID_T userId = storage.registUser(username);
    free(username);
    PACKAGE_T* pkgReply = createPackage(REGISTER_REPLY);
    if (userId != 0) {
        addItem(pkgReply, (void*)"OK", 3);
    } else {
        addItem(pkgReply, (void*)"Not OK", 7);
    }
    int retVal = sendPackage(logger, sock, pkgReply);
    freePackage(pkgReply);
    return retVal;
}