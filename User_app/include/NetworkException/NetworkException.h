#ifndef NETWORK_EXCEPTION_H
#define NETWORK_EXCEPTION_H

#include <stdexcept>
#include "NetworkException/NetworkError.h"

class NetworkException : public std::runtime_error {
private:
    NetworkError error;

public:
    NetworkException(
        NetworkError error,
        const std::string& message
    )
        : std::runtime_error(message),
          error(error)
    {}

    NetworkError getError() const {
        return error;
    }
};

#endif