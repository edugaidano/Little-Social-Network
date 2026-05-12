#include "../communication_controller.h"

int CommunicationController::deleteMessage(uint32_t messageId) {
    if (serverConnection == INVALID_SOCKET) {
        reconnectToServer();
    }

    PACKAGE_T* updatePkg = createPackage(DELETE_MESSAGE_REQUEST);
    addItem(updatePkg, (void*)username.c_str(), username.size() + 1);
    addItem(updatePkg, &messageId, sizeof(uint32_t));
    int retVal = sendPackage(logger, serverConnection, updatePkg);
    if (retVal != 0) {
        DIALOG_ERROR(nullptr, QObject::tr("Something went wrong while sending the delete request."));
        closeServerConnection();
        return -1;
    }

    PACKAGE_T* pkg = recvPackage(logger, serverConnection);
    QString recvErr = QObject::tr("Something went wrong while receiving the delete reply.");
    if (pkg == NULL) {
        DIALOG_ERROR(nullptr, recvErr);
        closeServerConnection();        
        return -1;
    }

    if (pkg->code != DELETE_MESSAGE_REPLY)  {
        freePackage(pkg);
        LOG_ERROR(logger, "Package received different to DELETE_MESSAGE_REPLY");
        DIALOG_ERROR(nullptr, recvErr);
        return -1;
    }

    LOG_DEBUG(logger, "DELETE_MESSAGE_REPLY received");

    char* item = (char*)getItem(pkg);
    freePackage(pkg);
    if (item == std::string("OK")) {
        LOG_INFO(logger, "Message deleted");
        free(item); 
        return 0;
    } else {
        LOG_ERROR(logger, "DELETE_MESSAGE_REPLY item diferent to OK");
        DIALOG_ERROR(nullptr, QObject::tr("Something went wrong at deleting."));
        free(item); 
        return -1;
    }
}