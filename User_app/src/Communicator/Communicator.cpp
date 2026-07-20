#include "Communicator.h"
#include "../make_connection/make_connection.h"

Communicator::Communicator(LOG_T& logger, std::string ip, std::string port)
    : logger(logger),
    ip(ip),
    port(port)
{
    connectToServer();
}

Communicator::~Communicator() {
    closesocket(serverConnection);
}

bool Communicator::serverConnectionIsOk() {
    if (serverConnection == INVALID_SOCKET) {
        LOG_ERROR(logger, "There isn't communication with the server.");
        return false;
    }
    return true;
}

void Communicator::connectToServer() {
    serverConnection = make_connection(logger, ip.c_str(), port.c_str());
}

void Communicator::closeServerConnection() {
    closesocket(serverConnection);
    serverConnection = INVALID_SOCKET;
}

int Communicator::send(PACKAGE_T* pkg) {
    if (!serverConnectionIsOk()) {
        LOG_INFO(logger, "Reconnecting to the server.");
        connectToServer();
        if (!serverConnectionIsOk())
            return -2;
    }
    return sendPackage(logger, serverConnection, pkg);
}

PACKAGE_T* Communicator::recv() {
        if (!serverConnectionIsOk()) {
        LOG_INFO(logger, "Reconnecting to the server.");
        connectToServer();
        if (!serverConnectionIsOk())
            return NULL;
    }
    return recvPackage(logger, serverConnection);
}