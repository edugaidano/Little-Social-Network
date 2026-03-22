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
            break;
        case MESSAGE_REQUEST:
            break;
        case SEND_MESSAGE:
            break;
        default:
            break;
        } 
        freePackage(pkg);
    }

    delete data;
    return NULL;
}