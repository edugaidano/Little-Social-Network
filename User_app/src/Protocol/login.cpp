#include "Protocol/login.h"
#include "ProtocolResult/ProtocolNetworkResult.h"
#include "NetworkException/NetworkException.h"

std::unique_ptr<ProtocolResult> loginProtocol(LOG_T& logger, Communicator& com, std::string& username, CODE_CONTENT& typeLogin) {
    LOG_DEBUG(logger, "Login protocol started");
    CODE_CONTENT replyCode;
    switch (typeLogin) {
    case LOGIN:
        replyCode = LOGIN_REPLY;
        break;
    case REGISTER:
        replyCode = REGISTER_REPLY;
        break;
    default:
        LOG_ERROR(logger, "typeLogin must be LOGIN or REGISTER");
        return std::make_unique<ProtocolResult>(ResultCode::ERROR_INTERNAL);
    }

    PACKAGE_T* pkgLogin = createPackage(typeLogin);
    addItem(pkgLogin, (void*)username.c_str(), username.size() + 1);

    PACKAGE_T* pkgReply;
    try {
        pkgReply = com.requestToServer(pkgLogin, replyCode);
    } catch (const NetworkException& e) {
        freePackage(pkgLogin);
        return std::make_unique<ProtocolNetworkResult>(ResultCode::ERROR_NETWORK, e.getError());
    }

    freePackage(pkgLogin);
    char* item = (char*)getItem(pkgReply);
    freePackage(pkgReply);

    if (item == std::string("OK")) {
        LOG_INFO(logger, "Login verified");
        free(item);
        return std::make_unique<ProtocolResult>(ResultCode::OK);
    }
    else {
        LOG_ERROR(logger, "Login refused");
        free(item);
        // TODO: explain why
        return std::make_unique<ProtocolResult>(ResultCode::REFUSED);
    }  
}