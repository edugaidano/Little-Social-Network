#include "../communication_controller.h"

bool CommunicationController::serverConectionIsOk() {
    if (serverConnection == INVALID_SOCKET) {
        DIALOG_ERROR(nullptr, QObject::tr("You do not have communication with the server.\nCheck if the configuration is correct"));
        return false;
    }
    return true;
}