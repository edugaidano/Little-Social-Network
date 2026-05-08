#include "../communication_controller.h"

int CommunicationController::login(const std::string& user, const CODE_CONTENT loginType) {
    if (loginType != LOGIN && loginType != REGISTER) {
        LOG_ERROR(logger, "loginType is diferent to LOGIN or REGISTER");
        Dialog d("ERROR", QObject::tr("Something went wrong."));
        d.exec();
        return -1;
    }

    if (serverConnection == INVALID_SOCKET) {
        reconnectToServer();   
        if (!serverConectionIsOk())
            return -1;
    }
    
    PACKAGE_T* pkgLogin = createPackage(loginType);
    addItem(pkgLogin, (void*)user.c_str(), user.size() + 1);
    int retVal = sendPackage(logger, serverConnection, pkgLogin);
    freePackage(pkgLogin);
    if (retVal != 0) {
        Dialog d("ERROR", QObject::tr("Something went wrong while sending the request."));
        d.exec();
        closeServerConnection();
        return -1;
    }

    PACKAGE_T* pkg = recvPackage(logger, serverConnection);
    QString recvErr = QObject::tr("Something went wrong while receiving the reply.");
    if (pkg == NULL) {
        Dialog d("ERROR", recvErr);
        d.exec();
        closeServerConnection();
        return -1;
    }  

    if (pkg->code != LOGIN_REPLY)  {
        freePackage(pkg);
        LOG_ERROR(logger, "Package received different to corresponding reply.");
        Dialog d("ERROR", recvErr);
        d.exec();
        return -1;
    }

    LOG_DEBUG(logger, "Reply received");

    char* item = (char*)getItem(pkg);
    freePackage(pkg);
    if (item == std::string("OK")) {
        LOG_INFO(logger, "Login verified");
        username = user;
        free(item);
        return 0;
    } else {
        LOG_ERROR(logger, "Login refused");
        QString logStr = QObject::tr("Login refused");
        // TODO: explain why
        Dialog d("ERROR", logStr);
        d.exec();
        free(item);
        return -1;
    }
}