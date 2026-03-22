#include "connect_server.h"

SOCKET connectToServer(LOG_T &logger, const char *ip, const char *port) {
	WSADATA wsa;
	int iResult = WSAStartup(MAKEWORD(2, 2), &wsa);
	if (iResult != 0) {
		LOG_ERROR(logger, "WSAStartup() failed: "+ std::to_string(iResult));
		return INVALID_SOCKET;
	}
	
	struct addrinfo *result = NULL, *ptr = NULL, hints;
	ZeroMemory( &hints, sizeof(hints) );
	hints.ai_family   = AF_UNSPEC;
	hints.ai_socktype = SOCK_STREAM;
	hints.ai_protocol = IPPROTO_TCP;
	
	iResult = getaddrinfo(ip, port, &hints, &result);
	if (iResult != 0) {
		LOG_ERROR(logger, "getaddrinfo() failed: " + std::to_string(iResult));
		WSACleanup();
		return INVALID_SOCKET;
	}

	SOCKET server_connection = INVALID_SOCKET;
	ptr = result;
	server_connection = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP); 

	if (server_connection == INVALID_SOCKET) {
		int err = WSAGetLastError();
		LOG_ERROR(logger, "Error at socket(): " + std::to_string(err));
		WSACleanup();
		return INVALID_SOCKET;
	}
	
	iResult = connect(server_connection, ptr->ai_addr, (int)ptr->ai_addrlen);
	if (iResult == SOCKET_ERROR) {
		int err = WSAGetLastError();
		LOG_ERROR(logger, "Connect error : " + std::to_string(err));
    	closesocket(server_connection);
    	return INVALID_SOCKET;
	}

	freeaddrinfo(result);
	
	if (server_connection == INVALID_SOCKET) {
		LOG_ERROR(logger, "Unable to connect to server!");
    	WSACleanup();
		return INVALID_SOCKET;
	}

	LOG_INFO(logger, "Successful connection to the server");
	return server_connection;
}