#include "send_message.h"

int sendMessage(LOG_T& logger, PACKAGE_T* messagePkg, SOCKET socket) {
    char* destinatary = (char*)getItem(messagePkg);
    //TODO: search if the destinatary exist
    bool exist = true;
    free(destinatary);

    char* date = (char*)getItem(messagePkg);
    char* sender = (char*)getItem(messagePkg);
    char* subject = (char*)getItem(messagePkg);
    char* content = (char*)getItem(messagePkg);
    //TODO: save new content
    free(date);
    free(sender);
    free(subject);
    free(content);
    PACKAGE_T* pkg = createPackage(SEND_REPLY);
    bool noProblems = true;
    if (noProblems) {
        addItem(pkg, (void*)"OK", 3);
    } else {
        addItem(pkg, (void*)"Not OK", 7);
    }
    int retVal = sendPackage(logger, socket, pkg);
    freePackage(pkg);
    return retVal;
}