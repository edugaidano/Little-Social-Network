#include "search_profile.h"

int searchProfile(LOG_T& logger, PACKAGE_T* searchPkg, SOCKET socket, UserIndex index) {
    char* username = (char*)getItem(searchPkg);
    ID_T userId = index.findUser(username);
    PACKAGE_T* profilePkg = createPackage(PROFILE);
    if (userId != 0) {
        addItem(profilePkg, username, std::string(username).size() + 1);
        free(username);
        std::ifstream profile(storagePath / PROFILES_DIR / std::to_string(userId));
        if (profile.is_open()) {
            std::stringstream content;
            content << profile.rdbuf();
            profile.close();
            addItem(profilePkg, (void*)content.str().c_str(), content.str().size() + 1);
        }
    }
    int retVal = sendPackage(logger, socket, profilePkg);
    freePackage(profilePkg);
    return retVal;
}