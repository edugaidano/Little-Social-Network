#include "Protocol/request_inbox.h"
#include "NetworkException/NetworkException.h"
#include "ProtocolResult/ProtocolNetworkResult.h"
#include "ProtocolResult/ProtocolInboxResult.h"

std::unique_ptr<ProtocolResult> requestInboxProtocol(LOG_T& logger, Communicator& com, std::string& username) {
    PACKAGE_T* requestPkg = createPackage(MESSAGES_REQUEST);
    addItem(requestPkg, (void*)username.c_str(), username.size() + 1);
    
    PACKAGE_T* recvdPkg;
    try {
        recvdPkg = com.requestToServer(requestPkg, MESSAGES);
    } catch (const NetworkException& e) {
        freePackage(requestPkg);
        return std::make_unique<ProtocolNetworkResult>(ResultCode::ERROR_NETWORK, e.getError());
    }

    freePackage(requestPkg);
    auto result = std::make_unique<ProtocolInboxResult>(ResultCode::OK);
    while (recvdPkg->bufferSize != 0) {
        uint32_t* idPtr = (uint32_t*)getItem(recvdPkg);
        uint8_t* seenPtr = (uint8_t*)getItem(recvdPkg);
        char* date = (char*)getItem(recvdPkg);
        char* sender = (char*)getItem(recvdPkg);
        char* subject = (char*)getItem(recvdPkg);

        result->addItem({*idPtr, *seenPtr, date, sender, subject});
        
        free(idPtr);
        free(seenPtr);
        free(date);
        free(sender);
        free(subject);
    }
    freePackage(recvdPkg);
    return result;
}