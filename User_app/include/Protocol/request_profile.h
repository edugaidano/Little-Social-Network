#ifndef REQUEST_PROFILE_PROTOCOL_H
#define REQUEST_PROFILE_PROTOCOL_H

#include <memory>
#include "Communicator.h"
#include "ProtocolResult/ProtocolResult.h"

std::unique_ptr<ProtocolResult> requestProfileProtocol(LOG_T& logger, Communicator& com, std::string& username);

#endif
