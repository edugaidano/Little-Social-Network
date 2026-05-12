#include "../communication_controller.h"

void CommunicationController::updateProfile(const std::string& newContent) {
    if (serverConnection == INVALID_SOCKET) {
        reconnectToServer();
    }

    PACKAGE_T* updatePkg = createPackage(UPDATE_PROFILE);
    addItem(updatePkg, (void*)username.c_str(), username.size() + 1);
    addItem(updatePkg, (void*)newContent.c_str(), newContent.size() + 1);
    int retVal = sendPackage(logger, serverConnection, updatePkg);
    if (retVal != 0) {
        DIALOG_ERROR(nullptr, QObject::tr("Something went wrong while sending the update request."));
        return;
    }

    PACKAGE_T* pkg = recvPackage(logger, serverConnection);
    QString recvErr = QObject::tr("Something went wrong while receiving the update reply.");
    if (pkg == NULL) {
        DIALOG_ERROR(nullptr, recvErr);
        return;
    }

    if (pkg->code != UPDATE_REPLY)  {
        freePackage(pkg);
        LOG_ERROR(logger, "Package received different to UPDATE_REPLY");
        DIALOG_ERROR(nullptr, recvErr);
        return;
    }

    LOG_DEBUG(logger, "UPDATE_REPLY received");

    char* item = (char*)getItem(pkg);
    freePackage(pkg);
    if (item == std::string("OK")) {
        LOG_INFO(logger, "Profile updated");
    } else {
        LOG_ERROR(logger, "UPDATE_REPLY item diferent to OK");
        DIALOG_ERROR(nullptr, QObject::tr("Something went wrong during the update."));
    }
    free(item);
}