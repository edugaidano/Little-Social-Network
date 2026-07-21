#ifndef PROTOCOL_RESULT_H
#define PROTOCOL_RESULT_H

#include "ProtocolResult/ResultCode.h"

class ProtocolResult {
private:
    ResultCode code;
public:
    ProtocolResult(ResultCode code) : code(code) {}
    virtual ~ProtocolResult() = default;

    ResultCode& getCode() {
        return code;
    }
};


#endif