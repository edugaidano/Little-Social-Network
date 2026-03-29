#include "send_message.h"

int sendMessage(LOG_T& logger, PACKAGE_T* messagePkg, SOCKET socket, UserIndex index) {
    char* destinatary = (char*)getItem(messagePkg);
    UserId_t destinataryId = index.findUser(destinatary);
    free(destinatary);

    bool noProblems = true;
    if (destinataryId == 0) {
        noProblems = false;
    } else {   
        char* date = (char*)getItem(messagePkg);
        char* sender = (char*)getItem(messagePkg);
        char* subject = (char*)getItem(messagePkg);
        char* content = (char*)getItem(messagePkg);
        //TODO: save new content
        free(date);
        free(sender);
        free(subject);
        free(content);
    }
    
    PACKAGE_T* pkg = createPackage(SEND_REPLY);
    if (noProblems) {
        addItem(pkg, (void*)"OK", 3);
    } else {
        addItem(pkg, (void*)"Not OK", 7);
    }
    int retVal = sendPackage(logger, socket, pkg);
    freePackage(pkg);
    return retVal;
}