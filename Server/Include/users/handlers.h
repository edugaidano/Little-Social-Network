#ifndef HANDLERS_H
#define HANDLERS_H

#include "storage/StorageController.h"
#include "communication/communication.h"

int handlerLoginRequest(LOG_T& logger, StorageController& storage, SOCKET_T& sock, PACKAGE_T* pkg);

int handlerRegistrationRequest(LOG_T& logger, StorageController& storage, SOCKET_T& sock, PACKAGE_T* pkg);

int handlerUpdateProfileRequest(LOG_T& logger, StorageController& storage, SOCKET_T& sock, PACKAGE_T* pkg);

int handlerSendMessageRequest(LOG_T& logger, StorageController& storage, SOCKET_T& sock, PACKAGE_T* pkg);

int handlerSearchProfileRequest(LOG_T& logger, StorageController& storage, SOCKET_T& sock, PACKAGE_T* pkg);

int handlerGetIndexRequest(LOG_T& logger, StorageController& storage, SOCKET_T& sock, PACKAGE_T* pkg);

int handlerGetMessageRequest(LOG_T& logger, StorageController& storage, SOCKET_T& sock, PACKAGE_T* pkg);

int handlerDeleteMessageRequest(LOG_T& logger, StorageController& storage, SOCKET_T& sock, PACKAGE_T* pkg);

#endif