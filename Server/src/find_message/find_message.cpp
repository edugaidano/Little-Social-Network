#include "find_message.h"

int findMessage(LOG_T& logger, PACKAGE_T* requestPkg, SOCKET socket) {
    char* username = (char*)getItem(requestPkg);
    uint32_t* messageId = (uint32_t*)getItem(requestPkg);
    //TODO: find the message
    free(username);
    free(messageId);
    bool noProblems = true;
    PACKAGE_T* pkg = createPackage(MESSAGE);
    if (noProblems) {
        addItem(pkg, (void*)"Content of the message selected", 32);
    }
    int retVal = sendPackage(logger, socket, pkg);
    freePackage(pkg);
    return retVal;
}