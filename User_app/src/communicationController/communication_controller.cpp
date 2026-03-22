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
    freePackage(pkgLogin);
    if (retVal != 0) {
        Dialog d("ERROR", "Something went wrong at sending the login request.\nCheck is the configuration is correct");
        d.exec();
        return -1;
    }

    PACKAGE_T* pkg = recvPackage(logger, serverConnection);
    char recvErr[50]("Something went wrong at receiving the login reply");
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

PROFILE_S* CommunicationController::searchRequest(const std::string& user) {
    PACKAGE_T* searchPkg = createPackage(SEARCH_PROFILE);
    addItem(searchPkg, (void*)user.c_str(), user.size() + 1);
    int retVal = sendPackage(logger, serverConnection, searchPkg);
    if (retVal != 0) {
        if (retVal != 0) {
        Dialog d("ERROR", "Something went wrong at sending the search request.");
        d.exec();
        return NULL;
        }
    }

    PACKAGE_T* pkg = recvPackage(logger, serverConnection);
    char recvErr[46]("Something went wrong at receiving the profile");
    if (pkg == NULL) {
        Dialog d("ERROR", recvErr);
        d.exec();
        return NULL;
    }

    if (pkg->code != PROFILE)  {
        freePackage(pkg);
        LOG_ERROR(logger, "Package received different to PROFILE");
        Dialog d("ERROR", recvErr);
        d.exec();
        return NULL;
    }

    LOG_DEBUG(logger, "PROFILE received");
    char* p_username = (char*)getItem(pkg);
    if (p_username == NULL) {
        freePackage(pkg);
        std::string errLog("The user " + user + " don't have a profile");
        LOG_WARNING(logger, errLog);
        Dialog d("WARNING", errLog.c_str());
        d.exec();
        return NULL;
    }

    if (p_username != user) {
        freePackage(pkg);
        LOG_ERROR(logger, "The profile received is different to the requested profile");
        Dialog d("ERROR", recvErr);
        d.exec();
        return NULL;
    }
    
    PROFILE_S* p = new PROFILE_S;
    p->username = p_username;
    p->content = (char*)getItem(pkg);
    freePackage(pkg);
    
    return p;
}

PROFILE_S* CommunicationController::myProfileRequest() {
    return searchRequest(username);
}
