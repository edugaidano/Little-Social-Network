#include "communication_controller.h"

CommunicationController::~CommunicationController() {
    if (serverConnection != INVALID_SOCKET)   
        closesocket(serverConnection);
}