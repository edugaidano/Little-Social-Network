#ifndef USER_MANAGER_H
#define USER_MANAGER_H

#include "../server_storage/server_storage.h"

// on Global folder
#include "communication/communication.h"

struct ThreadData {
    SOCKET clientSocket;
    LOG_T* logger;
    UserIndex* index;
};

void* userManager(void* usrSock);

int makeLogin(ThreadData* data, PACKAGE_T* pkg);
int makeRegistration(ThreadData* data, PACKAGE_T* pkg);
int updateProfile(ThreadData* data, PACKAGE_T* pkg);
int sendMessage(ThreadData* data, PACKAGE_T* pkg);
int searchProfile(ThreadData* data, PACKAGE_T* pkg);
int findMessagesList(ThreadData* data, PACKAGE_T* pkg);
int findMessage(ThreadData* data, PACKAGE_T* pkg);
int deleteMessage(ThreadData* data, PACKAGE_T* pkg);

#endif
