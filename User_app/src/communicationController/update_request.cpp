#include "communication_controller.h"

void CommunicationController::updateRequest(const std::string& newContent) {
    PACKAGE_T* updatePkg = createPackage(UPDATE_PROFILE);
    addItem(updatePkg, (void*)username.c_str(), username.size() + 1);
    addItem(updatePkg, (void*)newContent.c_str(), newContent.size() + 1);
    int retVal = sendPackage(logger, serverConnection, updatePkg);
    if (retVal != 0) {
        Dialog d("ERROR", "Something went wrong at sending the update request.");
        d.exec();
        return;
    }

    PACKAGE_T* pkg = recvPackage(logger, serverConnection);
    char recvErr[51]("Something went wrong at receiving the update reply");
    if (pkg == NULL) {
        Dialog d("ERROR", recvErr);
        d.exec();
        return;
    }

    if (pkg->code != UPDATE_REPLY)  {
        freePackage(pkg);
        LOG_ERROR(logger, "Package received different to UPDATE_REPLY");
        Dialog d("ERROR", recvErr);
        d.exec();
        return;
    }

    LOG_DEBUG(logger, "UPDATE_REPLY received");

    char* item = (char*)getItem(pkg);
    freePackage(pkg);
    if (item == std::string("OK")) {
        LOG_INFO(logger, "Profile updated");
    } else {
        std::string logStr("Problem during update");
        if (item == std::string("Not OK")) {
            logStr.append(": The profile isn't updated");
        }
        LOG_ERROR(logger, logStr);
        Dialog d("ERROR", logStr.c_str());
        d.exec();
    }
    free(item);
}