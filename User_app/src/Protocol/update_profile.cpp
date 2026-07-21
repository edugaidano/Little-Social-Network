#include "Protocol/update_profile.h"
#include "NetworkException/NetworkException.h"
#include "ProtocolResult/ProtocolNetworkResult.h"

std::unique_ptr<ProtocolResult> updateProfileProtocol(LOG_T& logger, Communicator& com, std::string& username, std::string& content) {
    LOG_DEBUG(logger, "Update profile protocol started.");
    PACKAGE_T* updatePkg = createPackage(UPDATE_PROFILE);
    addItem(updatePkg, (void*)username.c_str(), username.size() + 1);
    addItem(updatePkg, (void*)content.c_str(), content.size() + 1);

    PACKAGE_T* recvdPkg;
    try {
        recvdPkg = com.requestToServer(updatePkg, UPDATE_REPLY);
    } catch (const NetworkException& e) {
        freePackage(updatePkg);
        return std::make_unique<ProtocolNetworkResult>(ResultCode::ERROR_NETWORK, e.getError());
    }

    freePackage(updatePkg);
    char* item = (char*)getItem(recvdPkg);
    freePackage(recvdPkg);

    ResultCode result;
    if (item == std::string("OK")) {
        LOG_INFO(logger, "Profile updated");
        result = ResultCode::OK;
    } else {
        LOG_ERROR(logger, "UPDATE_REPLY item diferent to OK");
        result = ResultCode::ERROR_EXTERNAL;
    }
    free(item);
    return std::make_unique<ProtocolResult>(result);
}