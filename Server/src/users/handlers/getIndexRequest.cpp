#include "users/handlers.h"

int handlerGetIndexRequest(LOG_T& logger, StorageController& storage, SOCKET_T& sock, PACKAGE_T* pkg) {
    LOG_DEBUG(logger, "Start handlerGetIndexRequest");
    char* username = (char*)getItem(pkg);

    auto inbox = storage.getInbox(username);

    free(username);

    PACKAGE_T* pkgList = createPackage(MESSAGES);
    for (size_t i = inbox.size(); i-- > 0;) {
        auto& item = inbox[i];
        addItem(pkgList, &item.id, sizeof(ID_T));
        addItem(pkgList, &item.seen, sizeof(uint8_t));
        addItem(pkgList, item.date, std::string(item.date).size() + 1);
        addItem(pkgList, item.sender, std::string(item.sender).size() + 1);
        addItem(pkgList, item.subject, std::string(item.subject).size() + 1);
    }
    
    int retVal = sendPackage(logger, sock, pkgList);
    freePackage(pkgList);
    return retVal;
}