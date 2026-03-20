#include "communication.h"

void sendPackage(LOG_T& logger, SOCKET socket, PACKAGE_T* package) {
    LOG_DEBUG(logger, "Sending a package");
    void* serializedPkg = serializePackage(package);
    uint32_t totalSize = sizeof(CODE_CONTENT) + 2 * sizeof(uint32_t) + package->bufferSize; //TODO: revisar tamaños

    if (send(socket, (char*)serializedPkg, totalSize, 0) == SOCKET_ERROR) {
        int err = WSAGetLastError();
        LOG_ERROR(logger, "Failed to send the package: " + std::to_string(err));
        closesocket(socket);
        WSACleanup();
        freePackage(package);
        free(serializedPkg);
        exit(EXIT_FAILURE);
    }

    free(serializedPkg);
    LOG_DEBUG(logger, "Package sent");
}

PACKAGE_T* recvPackage(LOG_T& logger, SOCKET socket) {
    LOG_DEBUG(logger, "Waiting a package");
    int size;

    if (recv(socket, (char*)&size, sizeof(uint32_t), MSG_WAITALL) == SOCKET_ERROR) {
        int err = WSAGetLastError();
        LOG_ERROR(logger, "Failed to receive package size: " + std::to_string(err));
        closesocket(socket);
        WSACleanup();
        exit(EXIT_FAILURE);
    }

    LOG_DEBUG(logger, "size received: " + std::to_string(size));

    void* sPkg = malloc(size);

    if (recv(socket, (char*)sPkg, size, MSG_WAITALL) == SOCKET_ERROR) {
        int err = WSAGetLastError();
        LOG_ERROR(logger, "Failed to receive package data: " + std::to_string(err));
        closesocket(socket);
        WSACleanup();
        free(sPkg);
        exit(EXIT_FAILURE);
    }

    LOG_DEBUG(logger, "Serialized package received");

   PACKAGE_T* pkg = deserializePackage(sPkg);

    LOG_DEBUG(logger, "Package received");
    return pkg;
}