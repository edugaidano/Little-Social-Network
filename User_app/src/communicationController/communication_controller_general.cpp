#include "communication_controller.h"

CommunicationController::CommunicationController(LOG_T& logger, const char* ip, const char* port) : 
    logger(logger),
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
        Dialog d("ERROR", "You no have communication with the server.\nCheck is the configuration is correct");
        d.exec();
        return false;
    }
    return true;
}

PROFILE_S* CommunicationController::myProfileRequest() {
    return searchRequest(username);
}
