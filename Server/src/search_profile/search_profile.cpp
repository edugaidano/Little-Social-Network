#include "search_profile.h"

int searchProfile(LOG_T& logger, PACKAGE_T* searchPkg, SOCKET socket, UserIndex index) {
    char* username = (char*)getItem(searchPkg);
    UserId_t userId = index.findUser(username);
    PACKAGE_T* profilePkg = createPackage(PROFILE);
    if (userId != 0) {
        //TODO: use the real profile data
        addItem(profilePkg, username, std::string(username).size() + 1);
        free(username);
        addItem(profilePkg, (void*)"", 1);
    }
    int retVal = sendPackage(logger, socket, profilePkg);
    freePackage(profilePkg);
    return retVal;
}