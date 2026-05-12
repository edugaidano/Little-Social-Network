#include "../user_manager.h"

int updateProfile(ThreadData* data, PACKAGE_T* pkg) {
    char* username = (char*)getItem(pkg);
    ID_T userId = data->index->findUser(username);
    free(username);

    bool noProblems = true;
    if (userId == 0) {
        noProblems = false;
    } else {    
        auto mutexPtr = profileMutexManager.getMutex(userId);
        std::lock_guard<std::mutex> lock(*mutexPtr);

        char* newContent = (char*)getItem(pkg);
        std::ofstream profile(storagePath / PROFILES_DIR / std::to_string(userId));
        if (profile.is_open()) {
            profile << newContent;
        }
        free(newContent);
    }

    PACKAGE_T* pkgReply = createPackage(UPDATE_REPLY);
    if (noProblems) {
        addItem(pkgReply, (void*)"OK", 3);
    } else {
        addItem(pkgReply, (void*)"Not OK", 7);
    }
    int retVal = sendPackage(*data->logger, data->clientSocket, pkgReply);
    freePackage(pkgReply);
    return retVal;
}