#include "find_messages_list.h"

int findMessagesList(LOG_T& logger, PACKAGE_T* requestPkg, SOCKET socket, UserIndex index) {
    char* username = (char*)getItem(requestPkg);
    UserId_t userId = index.findUser(username);
    free(username);

    PACKAGE_T* pkg = createPackage(MESSAGES);
    if (userId != 0) {
        //Add all messages
        uint32_t messageId = 1;
        uint8_t seen = 0;
        addItem(pkg, &messageId, sizeof(uint32_t));
        addItem(pkg, &seen, sizeof(uint8_t));
        addItem(pkg, (void*)"20-03-2026", 11);
        addItem(pkg, (void*)"John Smith", 11);
        addItem(pkg, (void*)"Today is March 20th", 20);
    }
    int retVal = sendPackage(logger, socket, pkg);
    freePackage(pkg);
    return retVal;
}