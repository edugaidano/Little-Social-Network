#include "../communication_controller.h"

std::vector<MESSAGE_ITEM> CommunicationController::requestMessages() {
    if (serverConnection == INVALID_SOCKET) {
        reconnectToServer();
    }
    
    PACKAGE_T* requestPkg = createPackage(MESSAGES_REQUEST);
    addItem(requestPkg, (void*)username.c_str(), username.size() + 1);
    int retVal = sendPackage(logger, serverConnection, requestPkg);
    freePackage(requestPkg);

    if (retVal != 0) {
        Dialog d("ERROR", QObject::tr("Something went wrong while sending the messages request."));
        d.exec();
        closeServerConnection();
        return {};
    }

    PACKAGE_T* pkg = recvPackage(logger, serverConnection);
    QString recvErr = QObject::tr("Something went wrong while receiving the messages.");
    if (pkg == NULL) {
        Dialog d("ERROR", recvErr);
        d.exec();
        closeServerConnection();
        return {};
    }  

    if (pkg->code != MESSAGES)  {
        freePackage(pkg);
        LOG_ERROR(logger, "Package received different to MESSAGES");
        Dialog d("ERROR", recvErr);
        d.exec();
        return {};
    }

    LOG_DEBUG(logger, "MESSAGES received");

    if (pkg->bufferSize == 0){
        LOG_INFO(logger, "The user don't have messages");
        return {};
    }
        
    std::vector<MESSAGE_ITEM> msgs;
    while (pkg->bufferSize != 0) {
        MESSAGE_ITEM msg;
        uint32_t* idPtr = (uint32_t*)getItem(pkg);
        msg.id = *idPtr;
        free(idPtr);
        uint8_t* seenPtr = (uint8_t*)getItem(pkg);
        msg.seen = *seenPtr;
        free(seenPtr);
        msg.date = (char*)getItem(pkg);
        msg.sender = (char*)getItem(pkg);
        msg.subject = (char*)getItem(pkg);

        msgs.push_back(msg);
    }

    return msgs;
}