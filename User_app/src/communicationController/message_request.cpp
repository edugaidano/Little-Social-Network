#include "communication_controller.h"

char* CommunicationController::messageRequest(uint32_t messageId) {
    PACKAGE_T* updatePkg = createPackage(MESSAGE_REQUEST);
    addItem(updatePkg, (void*)username.c_str(), username.size() + 1);
    addItem(updatePkg, &messageId, sizeof(uint32_t));
    int retVal = sendPackage(logger, serverConnection, updatePkg);
    if (retVal != 0) {
        Dialog d("ERROR", "Something went wrong at sending the message request.");
        d.exec();
        return NULL;
    }

    PACKAGE_T* pkg = recvPackage(logger, serverConnection);
    char recvErr[52]("Something went wrong at receiving the message reply");
    if (pkg == NULL) {
        Dialog d("ERROR", recvErr);
        d.exec();
        return NULL;
    }

    if (pkg->code != MESSAGE)  {
        freePackage(pkg);
        LOG_ERROR(logger, "Package received different to MESSAGE");
        Dialog d("ERROR", recvErr);
        d.exec();
        return NULL;
    }

    LOG_DEBUG(logger, "MESSAGE received");

    char* item = (char*)getItem(pkg);
    freePackage(pkg);

    if (!item) {
        LOG_ERROR(logger, "No message content received");
        Dialog d("ERROR", recvErr);
        d.exec(); 
    }
    
    return item;
}