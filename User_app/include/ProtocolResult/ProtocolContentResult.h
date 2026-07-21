#ifndef PROTOCOL_CONTENT_RESULT_H
#define PROTOCOL_CONTENT_RESULT_H

#include <string>
#include "ProtocolResult/ProtocolResult.h"

class ProtocolContentResult : public ProtocolResult {
private:
    std::string content;
public:
    ProtocolContentResult(ResultCode code, std::string content) : ProtocolResult(code), content(content) {};
    
    std::string& getContent() {return content;}
};

#endif