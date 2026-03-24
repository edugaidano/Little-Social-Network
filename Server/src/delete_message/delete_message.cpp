#include "delete_message.h"

int deleteMessage(LOG_T& logger, PACKAGE_T* requestPkg, SOCKET socket) {
    char* username = (char*)getItem(requestPkg);
    uint32_t* newContent = (uint32_t*)getItem(requestPkg);
    //TODO: save new content
    free(username);
    free(newContent);
    PACKAGE_T* pkg = createPackage(DELETE_MESSAGE_REPLY);
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