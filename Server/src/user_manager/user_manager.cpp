#include "user_manager.h"

const std::unordered_map<CODE_CONTENT, int(*)(ThreadData* data, PACKAGE_T* pkg)> funcions = {
    { LOGIN, makeLogin },
    { REGISTER, makeRegistration },
    { SEARCH_PROFILE, searchProfile },
    { UPDATE_PROFILE, updateProfile },
    { MESSAGES_REQUEST, findMessagesList },
    { MESSAGE_REQUEST, findMessage },
    { DELETE_MESSAGE_REQUEST, deleteMessage },
    { SEND_MESSAGE, sendMessage }
};

void* userManager(void* threadData) {
    ThreadData* data = (ThreadData*)threadData;

    int lastOpRet = 0;
    while (lastOpRet == 0) {
        PACKAGE_T* pkg = recvPackage(*data->logger, data->clientSocket);

        if (pkg == NULL)
            break;

        auto it = funcions.find(pkg->code);

        if (it != funcions.end()) {
            lastOpRet = it->second(data, pkg);
        } else {
            LOG_ERROR(*data->logger, "The pkg code is not defined");
            lastOpRet = -1;
        }

        freePackage(pkg);
    }

    LOG_INFO(*data->logger, "Closing socket: " + std::to_string(data->clientSocket));
    closesocket(data->clientSocket);
    delete data;
    return NULL;
}