#ifndef COMMUNICATION_CONTROLLER_H
#define COMMUNICATION_CONTROLLER_H

#include "../connect_server/connect_server.h"

// on utils folder
#include "logs/logs.h"
#include "communication/communication.h"

class CommunicationController {
public:
    CommunicationController(LOG_T& logger, const char* ip, const char* port);
    ~CommunicationController();

    void loginRequest();
    void registerRequest();
    void searchRequest();
    void updateRequest();
    void messagesRequest();
    void messageRequest();
    void sendRequest();

private:
    SOCKET serverConnection;
    LOG_T& logger;
    void doHandshake();
};


#endif