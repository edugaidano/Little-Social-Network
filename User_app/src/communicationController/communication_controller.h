#ifndef COMMUNICATION_CONTROLLER_H
#define COMMUNICATION_CONTROLLER_H

#include <WinSock2.h>
#include <WS2tcpip.h>

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
    
    // loginType must be LOGIN or REGISTER, in other case the return value will be -1
    int login(const std::string& user, const CODE_CONTENT loginType);

    PROFILE_S* searchProfile(const std::string& user);
    PROFILE_S* searchOwnProfile();

    void updateProfile(const std::string& newContent);

    std::vector<MESSAGE_ITEM> requestMessages();

    char* requestMessageContent(uint32_t messageId);

    int deleteMessage(uint32_t messageId);

    void sendMessage(const std::string& destinatary, const std::string& subject, const std::string& content);
    
private:
    SOCKET serverConnection;
    
    LOG_T& logger;
    
    std::string username;
    std::string ip;
    std::string port;
    
    bool serverConectionIsOk();

    SOCKET makeConnection(const char *ip,const char *port);
    void reconnectToServer();
    void closeServerConnection();
};


#endif