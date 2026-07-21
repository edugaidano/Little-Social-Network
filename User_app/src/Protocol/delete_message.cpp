#include "Protocol/delete_message.h"
#include "NetworkException/NetworkException.h"
#include "ProtocolResult/ProtocolNetworkResult.h"

std::unique_ptr<ProtocolResult> deleteMessageProtocol(LOG_T& logger, Communicator& com, std::string& username, uint32_t& msgId) {
    LOG_DEBUG(logger, "Delete message protocol started");
    PACKAGE_T* requestPkg = createPackage(DELETE_MESSAGE_REQUEST);
    addItem(requestPkg, (void*)username.c_str(), username.size() + 1);
    addItem(requestPkg, &msgId, sizeof(uint32_t));
    PACKAGE_T* recvdPkg;
    try {
        recvdPkg = com.requestToServer(requestPkg, DELETE_MESSAGE_REPLY);
    }
    catch (const NetworkException& e) {
        freePackage(requestPkg);
        return std::make_unique<ProtocolNetworkResult>(ResultCode::ERROR_NETWORK, e.getError());
    }
    
    freePackage(requestPkg);
    char* item = (char*)getItem(recvdPkg);
    freePackage(recvdPkg);
    if (item == std::string("OK")) {
        LOG_INFO(logger, "Message deleted");
        free(item);
        return std::make_unique<ProtocolResult>(ResultCode::OK);
    } else {
        LOG_ERROR(logger, "DELETE_MESSAGE_REPLY item diferent to OK");
        free(item);
        return std::make_unique<ProtocolResult>(ResultCode::ERROR_EXTERNAL);
    }
}