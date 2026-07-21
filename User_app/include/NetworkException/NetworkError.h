#ifndef NETWORK_ERROR_H
#define NETWORK_ERROR_H

enum class NetworkError {
    SendError,
    ConnectionError,
    ReceiveError,
    UnexpectedPackage
};

#endif