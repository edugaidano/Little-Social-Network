#include "communication_controller.h"

CommunicationController::CommunicationController(LOG_T& logger, const char* ip, const char* port) : 
    logger(logger),
    username("")
{
    serverConnection = connectToServer(logger, ip, port);
}

CommunicationController::~CommunicationController() {
    if (serverConnection != INVALID_SOCKET)   
        closesocket(serverConnection);
}

bool CommunicationController::serverConectionIsOk() {
    if (serverConnection == INVALID_SOCKET) {
        Dialog d("ERROR", "You no have communication with the server.\nCheck is the configuration is correct");
        d.exec();
        return false;
    }
    return true;
}

int CommunicationController::loginRequest(const std::string& user) {
    if (!serverConectionIsOk())
        return -1;
    
    PACKAGE_T* pkgLogin = createPackage(LOGIN);
    addItem(pkgLogin, (void*)user.c_str(), user.size() + 1);
    int retVal = sendPackage(logger, serverConnection, pkgLogin);
    if (retVal != 0) {
        Dialog d("ERROR", "Something went wrong at sending the login request.\nCheck is the configuration is correct");
        d.exec();
        return -1;
    }
    freePackage(pkgLogin);

    PACKAGE_T* pkg = recvPackage(logger, serverConnection);
    char recvErr[50]("Something went wrong at receiving the login reply");
    if (pkg == NULL) {
        Dialog d("ERROR", recvErr);
        d.exec();
        return -1;
    }  

    if (pkg->code != LOGIN_REPLY)  {
        LOG_ERROR(logger, "Package received different to LOGIN_REPLY");
        Dialog d("ERROR", recvErr);
        d.exec();
        return -1;
    }

    LOG_DEBUG(logger, "LOGIN_REPLY received");

    char* item = (char*)getItem(pkg);
    if (item == std::string("OK")) {
        LOG_INFO(logger, "Login verified");
        username = user;
        free(item);
        return 0;
    } else {
        std::string logStr("Login refdused");
        if (item == std::string("Not OK")) {
            logStr.append(": The user don't exist");
        }
        LOG_ERROR(logger, logStr);
        Dialog d("ERROR", logStr.c_str());
        d.exec();
        free(item);
        return -1;
    }
}

int CommunicationController::registerRequest(const std::string& user) {
    if (!serverConectionIsOk())
        return -1;
    
    PACKAGE_T* pkgRegister = createPackage(REGISTER);
    addItem(pkgRegister, (void*)user.c_str(), user.size() + 1);
    int retVal = sendPackage(logger, serverConnection, pkgRegister);
    if (retVal != 0) {
        Dialog d("ERROR", "Something went wrong at sending the register request.\nCheck is the configuration is correct");
        d.exec();
        return -1;
    }
    freePackage(pkgRegister);

    PACKAGE_T* pkg = recvPackage(logger, serverConnection);
    char recvErr[53]("Something went wrong at receiving the register reply");
    if (pkg == NULL) {
        Dialog d("ERROR", recvErr);
        d.exec();
        return -1;
    }

    if (pkg->code != REGISTER_REPLY)  {
        LOG_ERROR(logger, "Package received different to REGISTER_REPLY");
        Dialog d("ERROR", recvErr);
        d.exec();
        return -1;
    }

    LOG_DEBUG(logger, "REGISTER_REPLY received");

    char* item = (char*)getItem(pkg);
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

