#include "users/handlers.h"

int handlerSendMessageRequest(LOG_T& logger, StorageController& storage, SOCKET_T& sock, PACKAGE_T* pkg) {
    LOG_DEBUG(logger, "Start handlerSendMessageRequest");
    char* destinatary = (char*)getItem(pkg);
    char* date = (char*)getItem(pkg);
    char* sender = (char*)getItem(pkg);
    char* subject = (char*)getItem(pkg);
    char* content = (char*)getItem(pkg);

    int result = storage.createMessage(destinatary, sender, date, subject, content);

    free(destinatary);
    free(date);
    free(sender);
    free(subject);
    free(content);
    
    PACKAGE_T* pkgReply = createPackage(SEND_REPLY);
    if (result == 0) {
        addItem(pkgReply, (void*)"OK", 3);
    } else {
        addItem(pkgReply, (void*)"Not OK", 7);
    }
    int retVal = sendPackage(logger, sock, pkgReply);
    freePackage(pkgReply);
    return retVal;
}