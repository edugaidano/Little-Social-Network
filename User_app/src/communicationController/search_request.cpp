#include "communication_controller.h"

PROFILE_S* CommunicationController::searchRequest(const std::string& user) {
    PACKAGE_T* searchPkg = createPackage(SEARCH_PROFILE);
    addItem(searchPkg, (void*)user.c_str(), user.size() + 1);
    int retVal = sendPackage(logger, serverConnection, searchPkg);
    if (retVal != 0) {
        Dialog d(
            "ERROR", 
            QObject::tr("Something went wrong while sending the search request.")
        );
        d.exec();
        return NULL;
    }

    PACKAGE_T* pkg = recvPackage(logger, serverConnection);
    QString recvErr = QObject::tr("Something went wrong while receiving the profile.");
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
        QString warningLog = QObject::tr("The user ");
        warningLog.append(user);
        warningLog.append(QObject::tr(" does not have a profile"));
        LOG_WARNING(logger, warningLog.toStdString());
        Dialog d("WARNING", warningLog);
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