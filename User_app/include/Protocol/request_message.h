#ifndef REQUEST_MESSAGE_PROTOCOL_H
#define REQUEST_MESSAGE_PROTOCOL_H

#include <memory>
#include "Communicator.h"
#include "ProtocolResult/ProtocolResult.h"

std::unique_ptr<ProtocolResult> requestMessageProtocol(LOG_T& logger, Communicator& com, std::string username, uint32_t& messageId);

#endif
