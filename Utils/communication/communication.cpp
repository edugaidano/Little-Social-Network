#include "communication.h"

int sendPackage(LOG_T& logger, SOCKET socket, PACKAGE_T* package) {
    LOG_DEBUG(logger, "Sending a package");
    void* serializedPkg = serializePackage(package);
    uint32_t totalSize = sizeof(CODE_CONTENT) + 2 * sizeof(uint32_t) + package->bufferSize;

    if (send(socket, (char*)serializedPkg, totalSize, 0) <= 0) {
        LOG_ERROR(logger, "Failed to send the package");
        closesocket(socket);
        free(serializedPkg);
        return -1;
    }

    free(serializedPkg);
    LOG_DEBUG(logger, "Package sent");
    return 0;
}

PACKAGE_T* recvPackage(LOG_T& logger, SOCKET socket) {
    LOG_DEBUG(logger, "Waiting a package");
    int size;

    if (recv(socket, (char*)&size, sizeof(uint32_t), MSG_WAITALL) <= 0) {     
        LOG_ERROR(logger, "Failed to receive package size");
        closesocket(socket);
        return NULL;
    }

    LOG_DEBUG(logger, "size received: " + std::to_string(size));

    void* sPkg = malloc(size);

    if (recv(socket, (char*)sPkg, size, MSG_WAITALL) <= 0) {
        LOG_ERROR(logger, "Failed to receive package data");
        closesocket(socket);
        free(sPkg);
        return NULL;
    }

    LOG_DEBUG(logger, "Serialized package received");

    PACKAGE_T* pkg = deserializePackage(sPkg);

    LOG_DEBUG(logger, "Package received");
    return pkg;
}