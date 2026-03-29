#include "update_profile.h"

int updateProfile(LOG_T& logger, PACKAGE_T* updatePkg, SOCKET socket, UserIndex index) {
    char* username = (char*)getItem(updatePkg);
    UserId_t userId = index.findUser(username);
    free(username);

    bool noProblems = true;
    if (userId == 0) {
        noProblems = false;
    } else {    
        char* newContent = (char*)getItem(updatePkg);
        //TODO: save new content
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