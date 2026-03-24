#include "communication_controller.h"

int CommunicationController::deleteRequest(uint32_t messageId) {
    PACKAGE_T* updatePkg = createPackage(DELETE_MESSAGE_REQUEST);
    addItem(updatePkg, (void*)username.c_str(), username.size() + 1);
    addItem(updatePkg, &messageId, sizeof(uint32_t));
    int retVal = sendPackage(logger, serverConnection, updatePkg);
    if (retVal != 0) {
        Dialog d("ERROR", "Something went wrong at sending the delete request.");
        d.exec();
        return retVal;
    }

    PACKAGE_T* pkg = recvPackage(logger, serverConnection);
    char recvErr[51]("Something went wrong at receiving the delete reply");
    if (pkg == NULL) {
        Dialog d("ERROR", recvErr);
        d.exec();
        return -1;
    }

    if (pkg->code != DELETE_MESSAGE_REPLY)  {
        freePackage(pkg);
        LOG_ERROR(logger, "Package received different to DELETE_MESSAGE_REPLY");
        Dialog d("ERROR", recvErr);
        d.exec();
        return -1;
    }

    LOG_DEBUG(logger, "DELETE_MESSAGE_REPLY received");

    char* item = (char*)getItem(pkg);
    freePackage(pkg);
    if (item == std::string("OK")) {
        LOG_INFO(logger, "Message deleted");
        retVal = 0;
    } else {
        std::string logStr("Problem at deleting");
        if (item == std::string("Not OK")) {
            logStr.append(": The message isn't deleted");
        }
        LOG_ERROR(logger, logStr);
        Dialog d("ERROR", logStr.c_str());
        d.exec();
        retVal = -1;
    }
    free(item); 
    return retVal;
}