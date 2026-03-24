#include "user_manager.h"

void* userManager(void* threadData) {
    ThreadData* data = (ThreadData*)threadData;

    int lastOpRet = 0;
    while (lastOpRet == 0) {
        PACKAGE_T* pkg = recvPackage(*data->logger, data->clientSocket);
        if (pkg == NULL)
            break;
        
        switch (pkg->code) {
        case LOGIN:
            lastOpRet = checkLogin(*data->logger, pkg, data->clientSocket);
            break;
        case REGISTER:
            lastOpRet = checkRegister(*data->logger, pkg, data->clientSocket);
            break;
        case SEARCH_PROFILE:
            lastOpRet = searchProfile(*data->logger, pkg, data->clientSocket);
            break;
        case UPDATE_PROFILE:
            lastOpRet = updateProfile(*data->logger, pkg, data->clientSocket);
            break;
        case MESSAGES_REQUEST:
            lastOpRet = findMessagesList(*data->logger, pkg, data->clientSocket);
            break;
        case MESSAGE_REQUEST:
            lastOpRet = findMessage(*data->logger, pkg, data->clientSocket);
            break;
        case DELETE_MESSAGE_REQUEST:
            lastOpRet = deleteMessage(*data->logger, pkg, data->clientSocket);
            break;
        case SEND_MESSAGE:
            lastOpRet = sendMessage(*data->logger, pkg, data->clientSocket);
            break;
        default:
            LOG_ERROR(*data->logger, "The pkg code is not defined");
            lastOpRet = -1;
            break;
        } 
        freePackage(pkg);
    }

    LOG_INFO(*data->logger, "Closing socket: " + std::to_string(data->clientSocket));
    closesocket(data->clientSocket);
    delete data;
    return NULL;
}