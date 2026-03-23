#ifndef COMMUNICATION_CONTROLLER_H
#define COMMUNICATION_CONTROLLER_H

#include "../connect_server/connect_server.h"
#include "../dialog/dialog.h"

// on utils folder
#include "logs/logs.h"
#include "communication/communication.h"

typedef struct PROFILE_S {
    char* username;
    char* content;
} PROFILE_S;

typedef struct MESSAGE_ITEM {
    uint32_t id;
    bool seen;
    char* date;
    char* sender;
    char* subject;
} MESSAGE_ITEM;

class CommunicationController {
public:
    CommunicationController(LOG_T& logger, const char* ip, const char* port);
    ~CommunicationController();
    
    int loginRequest(const std::string& user);
    int registerRequest(const std::string& user);

    PROFILE_S* searchRequest(const std::string& user);
    PROFILE_S* myProfileRequest();

    void updateRequest(const std::string& newContent);

    std::vector<MESSAGE_ITEM> messagesRequest();

    void messageRequest();
    void sendRequest();
    
    private:
    SOCKET serverConnection;
    
    LOG_T& logger;
    std::string username;
    
    bool serverConectionIsOk();
};


#endif