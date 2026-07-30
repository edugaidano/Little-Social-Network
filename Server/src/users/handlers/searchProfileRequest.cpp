#include "users/handlers.h"

int handlerSearchProfileRequest(LOG_T& logger, StorageController& storage, SOCKET_T& sock, PACKAGE_T* pkg) {
    LOG_DEBUG(logger, "Start handlerSearchProfileRequest");
    char* username = (char*)getItem(pkg);

    auto result = storage.getProfileContent(username);
     
    PACKAGE_T* profilePkg = createPackage(PROFILE);
    
    if (result.has_value()) {
        addItem(profilePkg, username, std::string(username).size() + 1);
        addItem(profilePkg, (void*)result.value().c_str(), result.value().size() + 1);
    }

    free(username);

    int retVal = sendPackage(logger, sock, profilePkg);
    freePackage(profilePkg);
    return retVal;
}