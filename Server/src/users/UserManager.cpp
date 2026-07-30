#include "users/UserManager.h"
#include "users/handlers.h"

UserManager::UserManager(LOG_T& logger, StorageController& storage, SOCKET_T usrSocket)
    : logger(logger),
    storage(storage),
    usrSocket(usrSocket)
{
    setHandlers();
    LOG_DEBUG(logger, "UserManager Created");
}

UserManager::~UserManager() {
    LOG_DEBUG(logger, "Deleting UserManager");
    closesocket(usrSocket);
}

void UserManager::setHandlers() {
    this->handlers = {
        { LOGIN, handlerLoginRequest },
        { REGISTER, handlerRegistrationRequest },
        { SEARCH_PROFILE, handlerSearchProfileRequest },
        { UPDATE_PROFILE, handlerUpdateProfileRequest },
        { MESSAGES_REQUEST, handlerGetIndexRequest},
        { MESSAGE_REQUEST, handlerGetMessageRequest },
        { DELETE_MESSAGE_REQUEST, handlerDeleteMessageRequest },
        { SEND_MESSAGE, handlerSendMessageRequest }
    };
}

void UserManager::manageUser() {
    int lastOpRet = 0;
    while (lastOpRet == 0) {
        PACKAGE_T* pkg = recvPackage(logger, usrSocket);

        if (pkg == NULL)
            break;

        auto it = handlers.find(pkg->code);

        if (it != handlers.end()) {
            lastOpRet = it->second(logger, storage, usrSocket, pkg);
        } else {
            LOG_ERROR(logger, "The pkg code is not defined");
            lastOpRet = -1;
        }

        freePackage(pkg);
    }
}