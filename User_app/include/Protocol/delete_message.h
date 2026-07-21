#ifndef DELETE_MESSAGE_PROTOCOL_H
#define DELETE_MESSAGE_PROTOCOL_H

#include <memory>
#include "Communicator.h"
#include "ProtocolResult/ProtocolResult.h"

std::unique_ptr<ProtocolResult> deleteMessageProtocol(LOG_T& logger, Communicator& com, std::string& username, uint32_t& msgId);

#endif