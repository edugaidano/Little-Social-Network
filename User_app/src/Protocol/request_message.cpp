#include "Protocol/request_message.h"
#include "NetworkException/NetworkException.h"
#include "ProtocolResult/ProtocolNetworkResult.h"
#include "ProtocolResult/ProtocolContentResult.h"

std::unique_ptr<ProtocolResult> requestMessageProtocol(LOG_T& logger, Communicator& com, std::string username, uint32_t& messageId) {
    LOG_DEBUG(logger, "Request message protocol started.");
    PACKAGE_T* requestPkg = createPackage(MESSAGE_REQUEST);
    addItem(requestPkg, (void*)username.c_str(), username.size() + 1);

    addItem(requestPkg, &messageId, sizeof(uint32_t));
    PACKAGE_T* recvdPkg;
    try {
        recvdPkg = com.requestToServer(requestPkg, MESSAGE);
    } catch (const NetworkException& e) {
        freePackage(requestPkg);
        return std::make_unique<ProtocolNetworkResult>(ResultCode::ERROR_NETWORK, e.getError());
    }

    freePackage(requestPkg);
    char* item = (char*)getItem(recvdPkg);
    freePackage(recvdPkg);

    if (!item) {
        LOG_ERROR(logger, "No message content received");
        return std::make_unique<ProtocolResult>(ResultCode::ERROR_EXTERNAL);
    } else {
        std::string content(item);
        free(item);
        return std::make_unique<ProtocolContentResult>(ResultCode::OK, content);
    }
}