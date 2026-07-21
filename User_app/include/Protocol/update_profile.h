#ifndef UPDATE_PROFILE_PROTOCOL_H
#define UPDATE_PROFILE_PROTOCOL_H

#include <memory>
#include "Communicator.h"
#include "ProtocolResult/ProtocolResult.h"

std::unique_ptr<ProtocolResult> updateProfileProtocol(LOG_T& logger, Communicator& com, std::string& username, std::string& content);

#endif
