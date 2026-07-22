#include "user_manager.h"

int searchProfile(ThreadData* data, PACKAGE_T* pkg) {
    char* username = (char*)getItem(pkg);
    ID_T userId = data->index->findUser(username);
    PACKAGE_T* profilePkg = createPackage(PROFILE);
    if (userId != 0) {
        auto mutexPtr = profileMutexManager.getMutex(userId);
        std::lock_guard<std::mutex> lock(*mutexPtr);

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
    int retVal = sendPackage(*data->logger, data->clientSocket, profilePkg);
    freePackage(profilePkg);
    return retVal;
}