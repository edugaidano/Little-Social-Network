#ifndef SERIALIZATION_H
#define SERIALIZATION_H

#include <cstdint>
#include <cstdlib>
#include <cstring>

typedef enum CODE_CONTENT : uint32_t {
    HANDSHAKE,
    RESULT_HANDSHAKE
} CODE_CONTENT;

typedef struct PACKAGE_T {
    CODE_CONTENT code;
    uint32_t bufferSize;
    void* buffer;
} PACKAGE_T;

PACKAGE_T* createPackage(CODE_CONTENT code);
void freePackage(PACKAGE_T* pkg);

void addItem(PACKAGE_T* pkg, void* data, uint32_t size);
void* getItem(PACKAGE_T* pkg);

void* serializePackage(PACKAGE_T* pkg);
PACKAGE_T* deserializePackage(void* sPkg);

#endif // SERIALIZATION_H