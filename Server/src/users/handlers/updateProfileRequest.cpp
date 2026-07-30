#include "users/handlers.h"

int handlerUpdateProfileRequest(LOG_T& logger, StorageController& storage, SOCKET_T& sock, PACKAGE_T* pkg) {
    LOG_DEBUG(logger, "Start handlerUpdateProfileRequest");
    char* username = (char*)getItem(pkg);
    char* newContent = (char*)getItem(pkg);
    
    int result = storage.updateProfile(username, newContent);
    
    free(username);
    free(newContent);
    
    PACKAGE_T* pkgReply = createPackage(UPDATE_REPLY);
    if (result == 0) {
        addItem(pkgReply, (void*)"OK", 3);
    } else {
        addItem(pkgReply, (void*)"Not OK", 7);
    }
    int retVal = sendPackage(logger, sock, pkgReply);
    freePackage(pkgReply);
    return retVal;
}