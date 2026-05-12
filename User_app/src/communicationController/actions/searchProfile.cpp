#include "../communication_controller.h"

PROFILE_S* CommunicationController::searchProfile(const std::string& user) {
    if (serverConnection == INVALID_SOCKET) {
        reconnectToServer();
    }
    
    PACKAGE_T* searchPkg = createPackage(SEARCH_PROFILE);
    addItem(searchPkg, (void*)user.c_str(), user.size() + 1);
    int retVal = sendPackage(logger, serverConnection, searchPkg);
    if (retVal != 0) {
        DIALOG_ERROR(nullptr, QObject::tr("Something went wrong while sending the search request."));
        closeServerConnection();
        return NULL;
    }

    PACKAGE_T* pkg = recvPackage(logger, serverConnection);
    QString recvErr = QObject::tr("Something went wrong while receiving the profile.");
    if (pkg == NULL) {
        DIALOG_ERROR(nullptr, recvErr);
        closeServerConnection();
        return NULL;
    }

    if (pkg->code != PROFILE)  {
        freePackage(pkg);
        LOG_ERROR(logger, "Package received different to PROFILE");
        DIALOG_ERROR(nullptr, recvErr);
        return NULL;
    }

    LOG_DEBUG(logger, "PROFILE received");
    char* p_username = (char*)getItem(pkg);
    if (p_username == NULL) {
        LOG_INFO(logger, "The user " + user + " does not have a profile");
        freePackage(pkg);
        DIALOG_INFO(nullptr, QObject::tr("The user ").append(user).append(QObject::tr(" does not have a profile")));
        return NULL;
    }

    if (p_username != user) {
        freePackage(pkg);
        LOG_ERROR(logger, "The profile received is different to the requested profile");
        DIALOG_ERROR(nullptr, recvErr);
        return NULL;
    }
    
    PROFILE_S* p = new PROFILE_S;
    p->username = p_username;
    p->content = (char*)getItem(pkg);
    freePackage(pkg);
    
    return p;
}