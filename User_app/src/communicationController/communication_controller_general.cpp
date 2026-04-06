#include "communication_controller.h"

CommunicationController::CommunicationController(LOG_T& logger, const char* ip, const char* port) : 
    logger(logger),
    ip(ip),
    port(port),
    username("")
{
    serverConnection = connectToServer(logger, ip, port);
}

CommunicationController::~CommunicationController() {
    if (serverConnection != INVALID_SOCKET)   
        closesocket(serverConnection);
}

bool CommunicationController::serverConectionIsOk() {
    if (serverConnection == INVALID_SOCKET) {
        Dialog d(
            "ERROR", 
            QObject::tr("You do not have communication with the server.\nCheck if the configuration is correct")
        );
        d.exec();
        return false;
    }
    return true;
}

void CommunicationController::reconectToServer() {
    serverConnection = connectToServer(logger, ip.c_str(), port.c_str());
}

void CommunicationController::closeServerConection() {
    closesocket(serverConnection);
    serverConnection = INVALID_SOCKET;
}

PROFILE_S* CommunicationController::myProfileRequest() {
    return searchRequest(username);
}