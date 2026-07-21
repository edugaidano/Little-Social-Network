#include "Protocol/send_message.h"
#include "NetworkException/NetworkException.h"
#include "ProtocolResult/ProtocolNetworkResult.h"

std::unique_ptr<ProtocolResult> sendMessageProtocol(LOG_T& logger, Communicator& com, std::string& sender, std::string destinatary, std::string subject, std::string content) {
    LOG_DEBUG(logger, "Send message protocol started.");

    std::time_t t = std::time(nullptr);
    std::tm tm{};

#ifdef _WIN32
    localtime_s(&tm, &t);
#else
    localtime_r(&t, &tm);
#endif

    std::ostringstream oss;
    oss << std::put_time(&tm, "%d - %m - %Y");

    PACKAGE_T* messagePkg = createPackage(SEND_MESSAGE);
    addItem(messagePkg, (void*)destinatary.c_str(), destinatary.size() + 1);
    addItem(messagePkg, (void*)oss.str().c_str(), oss.str().size() + 1);
    addItem(messagePkg, (void*)sender.c_str(), sender.size() + 1);
    addItem(messagePkg, (void*)subject.c_str(), subject.size() + 1);
    addItem(messagePkg, (void*)content.c_str(), content.size() + 1);

    PACKAGE_T* recvdPkg;
    try {
        recvdPkg = com.requestToServer(messagePkg, SEND_REPLY);
    } catch (const NetworkException& e) {
        freePackage(messagePkg);
        return std::make_unique<ProtocolNetworkResult>(ResultCode::ERROR_NETWORK, e.getError());
    }

    freePackage(messagePkg);
    char* item = (char*)getItem(recvdPkg);
    freePackage(recvdPkg);

    ResultCode result;
    if (item == std::string("OK")) {
        LOG_INFO(logger, "Message sended");
        result = ResultCode::OK;
    } else {
        LOG_ERROR(logger, "SEND_REPLY item diferent to OK");
        result = ResultCode::ERROR_EXTERNAL;
    }
    free(item);
    return std::make_unique<ProtocolResult>(result);
}