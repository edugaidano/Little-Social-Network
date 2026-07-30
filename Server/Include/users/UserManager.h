#ifndef USER_MANAGER_H
#define USER_MANAGER_H

#include <unordered_map>

#include "logs/logs.h"
#include "communication/communication.h"

#include "storage/StorageController.h"

class UserManager {
private:
    LOG_T& logger;
    StorageController& storage;
    SOCKET_T usrSocket;
    std::unordered_map<CODE_CONTENT, int(*)(LOG_T&, StorageController&, SOCKET_T&, PACKAGE_T*)> handlers;

    void setHandlers();
public:
    UserManager(LOG_T& logger, StorageController& storage, SOCKET_T usrSocket);
    ~UserManager();
    void manageUser();
};


#endif