#include "communication_controller.h"

int CommunicationController::registerRequest(const std::string& user) {
    if (!serverConectionIsOk())
        return -1;
    
    PACKAGE_T* pkgRegister = createPackage(REGISTER);
    addItem(pkgRegister, (void*)user.c_str(), user.size() + 1);
    int retVal = sendPackage(logger, serverConnection, pkgRegister);
    freePackage(pkgRegister);
    if (retVal != 0) {
        Dialog d(
            "ERROR", 
            QObject::tr("Something went wrong while sending the register request.\nCheck if the configuration is correct")
        );
        d.exec();
        return -1;
    }

    PACKAGE_T* pkg = recvPackage(logger, serverConnection);
    QString recvErr = QObject::tr("Something went wrong while receiving the register reply.");
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
        QString logStr = QObject::tr("Register refused");
        if (item == std::string("Not OK")) {
            logStr.append(QObject::tr(": The user already exists"));
        }
        LOG_ERROR(logger, logStr.toStdString());
        Dialog d("ERROR", logStr);
        d.exec();
        free(item);
        return -1;
    }
}