#include "../communication_controller.h"

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