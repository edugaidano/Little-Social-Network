#include "communication_controller.h"

CommunicationController::CommunicationController(LOG_T& logger, const char* ip, const char* port) 
    : logger(logger) 
{
    serverConnection = connectToServer(logger, ip, port);
    LOG_INFO(logger, "Successful connection to server");

    PACKAGE_T* pkgHandshake = createPackage(HANDSHAKE);
    sendPackage(logger, serverConnection, pkgHandshake);
    freePackage(pkgHandshake);

    PACKAGE_T* pkg = recvPackage(logger, serverConnection);
    if (pkg->code != RESULT_HANDSHAKE) {
        LOG_ERROR(logger, "Package received different to RESULT_HANDSHAKE");
        closesocket(serverConnection);
        exit(EXIT_FAILURE);
    }

    LOG_DEBUG(logger, "RESULT_HANDSHAKE received");
    
    char* data = (char*)getItem(pkg);

    LOG_INFO(logger, data);
}

CommunicationController::~CommunicationController() {
    closesocket(serverConnection);
}