#ifndef SEND_MESSAGE_PROTOCOL_H
#define SEND_MESSAGE_PROTOCOL_H

#include <memory>
#include "Communicator.h"
#include "ProtocolResult/ProtocolResult.h"

std::unique_ptr<ProtocolResult> sendMessageProtocol(LOG_T& logger, Communicator& com, std::string& sender, std::string destinatary, std::string subject, std::string content);

#endif
