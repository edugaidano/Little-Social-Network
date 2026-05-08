#include "../communication_controller.h"

void CommunicationController::closeServerConnection() {
    closesocket(serverConnection);
    serverConnection = INVALID_SOCKET;
}