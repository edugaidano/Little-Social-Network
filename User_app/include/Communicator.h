#ifndef COMMUNICATOR_H
#define COMMUNICATOR_H

#include "communication/communication.h"

class Communicator {
private:
    SOCKET serverConnection;
    std::string ip;
    std::string port;
    LOG_T& logger;

    bool serverConnectionIsOk();
    void connectToServer();
    void closeServerConnection();
public:
    Communicator(LOG_T& logger, std::string ip, std::string port);
    ~Communicator();

    int send(PACKAGE_T* pkg);
    PACKAGE_T* recv();

    //remind to use try-catch
    PACKAGE_T* requestToServer(PACKAGE_T* requestPkg, CODE_CONTENT replyCode);
};

#endif