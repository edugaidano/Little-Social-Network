#include "user_manager.h"

int findMessagesList(ThreadData* data, PACKAGE_T* pkg) {
    char* username = (char*)getItem(pkg);
    ID_T userId = data->index->findUser(username);
    free(username);

    PACKAGE_T* pkgList = createPackage(MESSAGES);
    if (userId != 0) {
        auto mutexPtr = messagesMutexManager.getMutex(userId);
        std::lock_guard<std::mutex> lock(*mutexPtr);
        
        std::ifstream index(storagePath / MESSAGES_DIR / std::to_string(userId) / MESSAGES_INDEX, std::ios::binary);
        while (true) {
            MESSAGE_ITEM item;
            if (!index.read(reinterpret_cast<char*>(&item), sizeof(MESSAGE_ITEM))) break;
            addItem(pkgList, &item.id, sizeof(ID_T));
            addItem(pkgList, &item.seen, sizeof(uint8_t));
            addItem(pkgList, item.date, std::string(item.date).size() + 1);
            addItem(pkgList, item.sender, std::string(item.sender).size() + 1);
            addItem(pkgList, item.subject, std::string(item.subject).size() + 1);
        }
    }
    int retVal = sendPackage(*data->logger, data->clientSocket, pkgList);
    freePackage(pkgList);
    return retVal;
}