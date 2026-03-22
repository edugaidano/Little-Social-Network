#include "update_profile.h"

int updateProfile(LOG_T& logger, PACKAGE_T* updatePkg, SOCKET socket) {
    char* username = (char*)getItem(updatePkg);
    char* newContent = (char*)getItem(updatePkg);
    //TODO: save new content
    free(username);
    free(newContent);
    PACKAGE_T* pkg = createPackage(UPDATE_REPLY);
    bool noProblems = true;
    if (noProblems) {
        addItem(pkg, (void*)"OK", 3);
    } else {
        addItem(pkg, (void*)"Not OK", 7);
    }
    int retVal = sendPackage(logger, socket, pkg);
    freePackage(pkg);
    return retVal;
}