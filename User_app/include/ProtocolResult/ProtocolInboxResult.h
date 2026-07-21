#ifndef PROTOCOL_INBOX_RESULT_H
#define PROTOCOL_INBOX_RESULT_H

#include <vector>
#include <string>
#include "ProtocolResult/ProtocolResult.h"

struct MessageItem {
    uint32_t id;
    uint8_t seen;
    std::string date;
    std::string sender;
    std::string subject;
};

class ProtocolInboxResult : public ProtocolResult {
private:
    std::vector<MessageItem> items;
public:
    ProtocolInboxResult(ResultCode code) : ProtocolResult(code) {};
    
    void addItem(MessageItem item) {
        this->items.push_back(item);
    }

    std::vector<MessageItem>& getItems() {
        return items;
    }
};

#endif