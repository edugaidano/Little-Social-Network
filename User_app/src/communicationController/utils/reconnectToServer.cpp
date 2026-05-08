#include "../communication_controller.h"

void CommunicationController::reconnectToServer() {
    serverConnection = makeConnection(ip.c_str(), port.c_str());
}