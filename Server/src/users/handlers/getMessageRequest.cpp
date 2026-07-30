#include "users/handlers.h"

int handlerGetMessageRequest(LOG_T& logger, StorageController& storage, SOCKET_T& sock, PACKAGE_T* pkg) {
    LOG_DEBUG(logger, "Start handlerGetMessageRequest");
    char* username = (char*)getItem(pkg);
    uint32_t* messageId = (uint32_t*)getItem(pkg);

    auto result = storage.getMessageContent(username, *messageId);

    free(username);
    free(messageId);

    PACKAGE_T* pkgMessage = createPackage(MESSAGE);
    if (result.has_value()) {
        addItem(pkgMessage, (void*)result.value().c_str(), result.value().size() + 1);
    }
    
    int retVal = sendPackage(logger, sock, pkgMessage);
    freePackage(pkgMessage);
    return retVal;
}