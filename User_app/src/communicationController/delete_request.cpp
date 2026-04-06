#include "communication_controller.h"

int CommunicationController::deleteRequest(uint32_t messageId) {
    if (serverConnection == INVALID_SOCKET) {
        reconectToServer();
    }
    PACKAGE_T* updatePkg = createPackage(DELETE_MESSAGE_REQUEST);
    addItem(updatePkg, (void*)username.c_str(), username.size() + 1);
    addItem(updatePkg, &messageId, sizeof(uint32_t));
    int retVal = sendPackage(logger, serverConnection, updatePkg);
    if (retVal != 0) {
        Dialog d(
            "ERROR", 
            QObject::tr("Something went wrong while sending the delete request.")
        );
        d.exec();
        closeServerConection();
        return -1;
    }

    PACKAGE_T* pkg = recvPackage(logger, serverConnection);
    QString recvErr = QObject::tr("Something went wrong while receiving the delete reply.");
    if (pkg == NULL) {
        Dialog d("ERROR", recvErr);
        d.exec();
        closeServerConection();        
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
        QString logStr = QObject::tr("Problem deleting");
        if (item == std::string("Not OK")) {
            logStr.append(QObject::tr(": The message was not deleted"));
        }
        LOG_ERROR(logger, logStr.toStdString());
        Dialog d("ERROR", logStr);
        d.exec();
        retVal = -1;
    }
    free(item); 
    return retVal;
}