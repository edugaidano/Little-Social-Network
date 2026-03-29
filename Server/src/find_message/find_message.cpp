#include "find_message.h"

int findMessage(LOG_T& logger, PACKAGE_T* requestPkg, SOCKET socket, UserIndex index) {
    char* username = (char*)getItem(requestPkg);
    UserId_t userId = index.findUser(username);
    free(username);

    bool noProblems = true;
    if (userId == 0) {
        noProblems = false;
    } else {
        uint32_t* messageId = (uint32_t*)getItem(requestPkg);
        //TODO: find the message
        free(messageId);
    }
    
    PACKAGE_T* pkg = createPackage(MESSAGE);
    if (noProblems) {
        addItem(pkg, (void*)"Content of the message selected", 32);
    }
    int retVal = sendPackage(logger, socket, pkg);
    freePackage(pkg);
    return retVal;
}