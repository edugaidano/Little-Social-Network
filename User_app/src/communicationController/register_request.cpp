#include "communication_controller.h"

int CommunicationController::registerRequest(const std::string& user) {
    if (!serverConectionIsOk())
        return -1;
    
    PACKAGE_T* pkgRegister = createPackage(REGISTER);
    addItem(pkgRegister, (void*)user.c_str(), user.size() + 1);
    int retVal = sendPackage(logger, serverConnection, pkgRegister);
    freePackage(pkgRegister);
    if (retVal != 0) {
        Dialog d("ERROR", "Something went wrong at sending the register request.\nCheck is the configuration is correct");
        d.exec();
        return -1;
    }

    PACKAGE_T* pkg = recvPackage(logger, serverConnection);
    char recvErr[53]("Something went wrong at receiving the register reply");
    if (pkg == NULL) {
        Dialog d("ERROR", recvErr);
        d.exec();
        return -1;
    }

    if (pkg->code != REGISTER_REPLY)  {
        freePackage(pkg);
        LOG_ERROR(logger, "Package received different to REGISTER_REPLY");
        Dialog d("ERROR", recvErr);
        d.exec();
        return -1;
    }

    LOG_DEBUG(logger, "REGISTER_REPLY received");

    char* item = (char*)getItem(pkg);
    freePackage(pkg);
    if (item == std::string("OK")) {
        LOG_INFO(logger, "Register verified");
        username = user;
        free(item);
        return 0;
    } else {
        std::string logStr("Register refdused");
        if (item == std::string("Not OK")) {
            logStr.append(": The user exist");
        }
        LOG_ERROR(logger, logStr);
        Dialog d("ERROR", logStr.c_str());
        d.exec();
        free(item);
        return -1;
    }
}