#include "update_profile.h"

int updateProfile(LOG_T& logger, PACKAGE_T* updatePkg, SOCKET socket, UserIndex index) {
    char* username = (char*)getItem(updatePkg);
    ID_T userId = index.findUser(username);
    free(username);

    bool noProblems = true;
    if (userId == 0) {
        noProblems = false;
    } else {    
        auto mutexPtr = profileMutexManager.getMutex(userId);
        std::lock_guard<std::mutex> lock(*mutexPtr);

        char* newContent = (char*)getItem(updatePkg);
        std::ofstream profile(storagePath / PROFILES_DIR / std::to_string(userId));
        if (profile.is_open()) {
            profile << newContent;
        }
        free(newContent);
    }

    PACKAGE_T* pkg = createPackage(UPDATE_REPLY);
    if (noProblems) {
        addItem(pkg, (void*)"OK", 3);
    } else {
        addItem(pkg, (void*)"Not OK", 7);
    }
    int retVal = sendPackage(logger, socket, pkg);
    freePackage(pkg);
    return retVal;
}