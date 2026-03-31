#include "communication_controller.h"

int CommunicationController::loginRequest(const std::string& user) {
    if (!serverConectionIsOk())
        return -1;
    
    PACKAGE_T* pkgLogin = createPackage(LOGIN);
    addItem(pkgLogin, (void*)user.c_str(), user.size() + 1);
    int retVal = sendPackage(logger, serverConnection, pkgLogin);
    freePackage(pkgLogin);
    if (retVal != 0) {
        Dialog d(
            "ERROR", 
            QObject::tr("Something went wrong while sending the login request.\nCheck if the configuration is correct")
        );
        d.exec();
        return -1;
    }

    PACKAGE_T* pkg = recvPackage(logger, serverConnection);
    QString recvErr = QObject::tr("Something went wrong while receiving the login reply.");
    if (pkg == NULL) {
        Dialog d("ERROR", recvErr);
        d.exec();
        return -1;
    }  

    if (pkg->code != LOGIN_REPLY)  {
        freePackage(pkg);
        LOG_ERROR(logger, "Package received different to LOGIN_REPLY");
        Dialog d("ERROR", recvErr);
        d.exec();
        return -1;
    }

    LOG_DEBUG(logger, "LOGIN_REPLY received");

    char* item = (char*)getItem(pkg);
    freePackage(pkg);
    if (item == std::string("OK")) {
        LOG_INFO(logger, "Login verified");
        username = user;
        free(item);
        return 0;
    } else {
        QString logStr = QObject::tr("Login refused");
        if (item == std::string("Not OK")) {
            logStr.append(QObject::tr(": The user does not exist"));
        }
        LOG_ERROR(logger, logStr.toStdString());
        Dialog d("ERROR", logStr);
        d.exec();
        free(item);
        return -1;
    }
}