#include "Communicator.h"
#include "make_connection/make_connection.h"
#include "NetworkException/NetworkException.h"

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

PACKAGE_T* Communicator::requestToServer(PACKAGE_T* requestPkg, CODE_CONTENT replyCode) {
    int sendRet = this->send(requestPkg); 
    if (sendRet == -1) {
        throw NetworkException(NetworkError::SendError, "Error sending request.");
        //tr("Something went wrong while sending the request to the server.")
    } else if (sendRet == -2) { 
        throw NetworkException(NetworkError::ConnectionError, "Error connecting to server.");
        //tr("Error at make connection with the server,\n check if the configuration is correct.")
    }
    
    PACKAGE_T* replyPkg = this->recv();
    if (replyPkg == NULL) {
        throw NetworkException(NetworkError::ReceiveError, "Error receiving the reply.");
        //tr("Something went wrong while receiving the reply from the server.")
    } else if (replyPkg->code != replyCode)  {
        freePackage(replyPkg);
        //tr("The package received is different from what was expected.")
        throw NetworkException(NetworkError::UnexpectedPackage, "Package received is different.");
    }
    
    return replyPkg;
}