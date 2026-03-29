#include "delete_message.h"

int deleteMessage(LOG_T& logger, PACKAGE_T* requestPkg, SOCKET socket, UserIndex index) {
    char* username = (char*)getItem(requestPkg);
    UserId_t userId = index.findUser(username);
    free(username);

    bool noProblems = true;
    if (userId == 0) {
        noProblems = false;
    } else {   
        uint32_t* newContent = (uint32_t*)getItem(requestPkg);
        //TODO: save new content
        free(newContent);
    }

    PACKAGE_T* pkg = createPackage(DELETE_MESSAGE_REPLY);
    if (noProblems) {
        addItem(pkg, (void*)"OK", 3);
    } else {
        addItem(pkg, (void*)"Not OK", 7);
    }
    int retVal = sendPackage(logger, socket, pkg);
    freePackage(pkg);
    return retVal;
}