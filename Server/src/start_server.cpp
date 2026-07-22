#include "start_server.h"

SOCKET startServer(LOG_T &logger, std::string &port) {
    WSADATA wsaData;
    int iResult;

    SOCKET listenSocket = INVALID_SOCKET;

    struct addrinfo *result = NULL;
    struct addrinfo hints;
    
    // Initialize Winsock
    iResult = WSAStartup(MAKEWORD(2,2), &wsaData);
    if (iResult != 0) {
        LOG_ERROR(logger, "WSAStartup() failed with error: " + std::to_string(iResult));
        exit(EXIT_FAILURE);
    }

    ZeroMemory(&hints, sizeof(hints));
    hints.ai_family = AF_INET;
    hints.ai_socktype = SOCK_STREAM;
    hints.ai_protocol = IPPROTO_TCP;
    hints.ai_flags = AI_PASSIVE;

    iResult = getaddrinfo(NULL, port.c_str(), &hints, &result);
    if ( iResult != 0 ) {
        LOG_ERROR(logger, "getaddrinfo() failed with error: " + std::to_string(iResult));
        WSACleanup();
        exit(EXIT_FAILURE);
    }

    // Create a SOCKET for the server to listen for client connections.
    listenSocket = socket(result->ai_family, result->ai_socktype, result->ai_protocol);
    if (listenSocket == INVALID_SOCKET) {
        LOG_ERROR(logger, "socket() failed with error: " + std::to_string(WSAGetLastError()));
        freeaddrinfo(result);
        WSACleanup();
        exit(EXIT_FAILURE);
    }

    // Setup the TCP listening socket
    iResult = bind(listenSocket, result->ai_addr, (int)result->ai_addrlen);
    if (iResult == SOCKET_ERROR) {
        LOG_ERROR(logger, "bind() failed with error: " + std::to_string(WSAGetLastError()));
        freeaddrinfo(result);
        closesocket(listenSocket);
        WSACleanup();
        exit(EXIT_FAILURE);
    }

    freeaddrinfo(result);

    iResult = listen(listenSocket, SOMAXCONN);
    if (iResult == SOCKET_ERROR) {
        LOG_ERROR(logger, "listen() failed with error: " + std::to_string(WSAGetLastError()));
        closesocket(listenSocket);
        WSACleanup();
        exit(EXIT_FAILURE);
    }

    LOG_INFO(logger, "Server is listening on port " + port);
    
    return listenSocket;
}