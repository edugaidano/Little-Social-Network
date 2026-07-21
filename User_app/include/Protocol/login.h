#ifndef LOGIN_PROTOCOL_H
#define LOGIN_PROTOCOL_H

#include <memory>
#include "Communicator.h"
#include "ProtocolResult/ProtocolResult.h"

std::unique_ptr<ProtocolResult> loginProtocol(LOG_T& logger, Communicator& com, std::string& username, CODE_CONTENT& typeLogin);

#endif
