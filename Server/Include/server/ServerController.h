#ifndef SERVER_CONTROLLER_H
#define SERVER_CONTROLLER_H

#include "logs/logs.h"

#include "server/start_server.h"
#include "storage/StorageController.h"

class ServerController {
private:
    LOG_T logger;
    SOCKET listenSocket;
    StorageController* storage;
public:
    ServerController();
    ~ServerController();
    void manageConnection();
};


#endif