#include "users/handlers.h"

int handlerDeleteMessageRequest(LOG_T& logger, StorageController& storage, SOCKET_T& sock, PACKAGE_T* pkg) {
    LOG_DEBUG(logger, "Start handlerDeleteMessageRequest");
    char* username = (char*)getItem(pkg);
    ID_T* messageId = (ID_T*)getItem(pkg);

    int result = storage.deleteMessage(username, *messageId);

    free(username);
    free(messageId);

    PACKAGE_T* pkgReply = createPackage(DELETE_MESSAGE_REPLY);
    if (result == 0) {
        addItem(pkgReply, (void*)"OK", 3);
    } else {
        addItem(pkgReply, (void*)"Not OK", 7);
    }
    int retVal = sendPackage(logger, sock, pkgReply);
    freePackage(pkgReply);
    return retVal;
}