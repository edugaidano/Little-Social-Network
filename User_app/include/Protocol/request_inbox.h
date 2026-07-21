#ifndef REQUEST_INBOX_PROTOCOL_H
#define REQUEST_INBOX_PROTOCOL_H

#include <memory>
#include "Communicator.h"
#include "ProtocolResult/ProtocolResult.h"

std::unique_ptr<ProtocolResult> requestInboxProtocol(LOG_T& logger, Communicator& com, std::string& username);

#endif
