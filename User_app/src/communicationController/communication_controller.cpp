#include "communication_controller.h"

CommunicationController::CommunicationController(LOG_T& logger, const char* ip, const char* port) : 
    logger(logger),
    username("")
{
    serverConnection = connectToServer(logger, ip, port);
}

CommunicationController::~CommunicationController() {
    closesocket(serverConnection);
}

int CommunicationController::loginRequest(const std::string& user) {
    PACKAGE_T* pkgLogin = createPackage(LOGIN);
    addItem(pkgLogin, (void*)user.c_str(), user.size() + 1);
    int retVal = sendPackage(logger, serverConnection, pkgLogin);
    freePackage(pkgLogin);
    if (retVal != 0)
        return -1;

    PACKAGE_T* pkg = recvPackage(logger, serverConnection);
    if (pkg == NULL)
        return -1;    

    if (pkg->code != LOGIN_REPLY)  {
        LOG_ERROR(logger, "Package received different to LOGIN_REPLY");
        closesocket(serverConnection);
        exit(EXIT_FAILURE);
    }

    LOG_DEBUG(logger, "LOGIN_REPLY received");

    char* item = (char*)getItem(pkg);
    if (item == std::string("OK")) {
        LOG_INFO(logger, "login verified");
        username = user;
        free(item);
        return 0;
    } else {
        LOG_ERROR(logger, "login refdused");
        free(item);
        return -1;
    }
}

int CommunicationController::registerRequest(const std::string& user) {
    PACKAGE_T* pkgRegister = createPackage(REGISTER);
    addItem(pkgRegister, (void*)user.c_str(), user.size() + 1);
    int retVal = sendPackage(logger, serverConnection, pkgRegister);
    freePackage(pkgRegister);
    if (retVal != 0)
        return -1;

    PACKAGE_T* pkg = recvPackage(logger, serverConnection);
    if (pkg == NULL)
        return -1; 

    if (pkg->code != REGISTER_REPLY)  {
        LOG_ERROR(logger, "Package received different to REGISTER_REPLY");
        closesocket(serverConnection);
        exit(EXIT_FAILURE);
    }

    LOG_DEBUG(logger, "REGISTER_REPLY received");

    char* item = (char*)getItem(pkg);
    if (item == std::string("OK")) {
        LOG_INFO(logger, "register verified");
        username = user;
        free(item);
        return 0;
    } else {
        LOG_ERROR(logger, "register refdused");
        free(item);
        return -1;
    }
}

