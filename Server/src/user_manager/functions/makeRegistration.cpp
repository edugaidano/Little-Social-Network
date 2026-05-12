#include "../user_manager.h"

int makeRegistration(ThreadData* data, PACKAGE_T* pkg) {
    char* username = (char*)getItem(pkg);
    ID_T userId = data->index->createUser(username);
    free(username);
    PACKAGE_T* pkgReply = createPackage(REGISTER_REPLY);
    if (userId != 0) {
        addItem(pkgReply, (void*)"OK", 3);
    } else {
        addItem(pkgReply, (void*)"Not OK", 7);
    }
    int retVal = sendPackage(*data->logger, data->clientSocket, pkgReply);
    freePackage(pkgReply);
    return retVal;
}