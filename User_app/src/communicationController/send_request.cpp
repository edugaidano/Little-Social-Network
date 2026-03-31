#include "communication_controller.h"

void CommunicationController::sendRequest(const std::string& destinatary, const std::string& subject, const std::string& content) {

    std::time_t t = std::time(nullptr);
    std::tm tm{};

#ifdef _WIN32
    localtime_s(&tm, &t);
#else
    localtime_r(&t, &tm);
#endif

    std::ostringstream oss;
    oss << std::put_time(&tm, "%d - %m - %Y");

    PACKAGE_T* updatePkg = createPackage(SEND_MESSAGE);
    addItem(updatePkg, (void*)destinatary.c_str(), destinatary.size() + 1);
    addItem(updatePkg, (void*)oss.str().c_str(), oss.str().size() + 1);
    addItem(updatePkg, (void*)username.c_str(), username.size() + 1);
    addItem(updatePkg, (void*)subject.c_str(), subject.size() + 1);
    addItem(updatePkg, (void*)content.c_str(), content.size() + 1);
    int retVal = sendPackage(logger, serverConnection, updatePkg);
    if (retVal != 0) {
        Dialog d("ERROR", QObject::tr("Something went wrong while sending the message."));
        d.exec();
        return;
    }

    PACKAGE_T* pkg = recvPackage(logger, serverConnection);
    QString recvErr = QObject::tr("Something went wrong while receiving the send reply.");
    if (pkg == NULL) {
        Dialog d("ERROR", recvErr);
        d.exec();
        return;
    }

    if (pkg->code != SEND_REPLY)  {
        freePackage(pkg);
        LOG_ERROR(logger, "Package received different to SEND_REPLY");
        Dialog d("ERROR", recvErr);
        d.exec();
        return;
    }

    LOG_DEBUG(logger, "SEND_REPLY received");

    char* item = (char*)getItem(pkg);
    freePackage(pkg);
    if (item == std::string("OK")) {
        LOG_INFO(logger, "Message sended");
        Dialog d("INFO", QObject::tr("Message sent"));
        d.exec();
    } else {
        QString logStr = QObject::tr("Problem sending");
        if (item == std::string("Not OK")) {
            logStr.append(QObject::tr(": The message was not sent"));
        }
        LOG_ERROR(logger, logStr.toStdString());
        Dialog d("ERROR", logStr);
        d.exec();
    }
    free(item);
}