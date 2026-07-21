#include "Protocol/request_profile.h"
#include "NetworkException/NetworkException.h"
#include "ProtocolResult/ProtocolNetworkResult.h"
#include "ProtocolResult/ProtocolContentResult.h"

std::unique_ptr<ProtocolResult> requestProfileProtocol(LOG_T& logger, Communicator& com, std::string& username) {
    LOG_DEBUG(logger, "Request profile protocol started.");
    PACKAGE_T* requestPkg = createPackage(SEARCH_PROFILE);
    addItem(requestPkg, (void*)username.c_str(), username.size() + 1);
    PACKAGE_T* recvdPkg;
    try {
        recvdPkg = com.requestToServer(requestPkg, PROFILE);
    } catch (const NetworkException& e) {
        freePackage(requestPkg);
        return std::make_unique<ProtocolNetworkResult>(ResultCode::ERROR_NETWORK, e.getError());
    }

    freePackage(requestPkg);
    char* usr = (char*)getItem(recvdPkg);

    if (usr == NULL) {
        LOG_INFO(logger, "The user doesn't have a profile");
        freePackage(recvdPkg);
        return std::make_unique<ProtocolResult>(ResultCode::NOT_FIND);
    }

    if (usr != username) {
        LOG_ERROR(logger, "The profile received is different to the requested profile");
        free(usr);
        freePackage(recvdPkg);
        return std::make_unique<ProtocolResult>(ResultCode::ERROR_EXTERNAL);
    }

    free(usr);
    char* c = (char*)getItem(recvdPkg);
    freePackage(recvdPkg);
    std::string content(c);
    free(c);
    return std::make_unique<ProtocolContentResult>(ResultCode::OK, content);
}