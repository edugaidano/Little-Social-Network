#ifndef PROTOCOL_NETWORK_RESULT_H
#define PROTOCOL_NETWORK_RESULT_H

#include "ProtocolResult/ProtocolResult.h"
#include "NetworkException/NetworkError.h"

class ProtocolNetworkResult : public ProtocolResult {
private:
    NetworkError error;
public:
    ProtocolNetworkResult(ResultCode code, NetworkError error) : ProtocolResult(code), error(error) {};
    
    NetworkError getError() {return error;}
};

#endif