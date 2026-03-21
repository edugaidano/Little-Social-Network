#include "serialization.h"

PACKAGE_T* createPackage(CODE_CONTENT code) {
    PACKAGE_T* pkg = new PACKAGE_T;
    pkg->code = code;
    pkg->bufferSize = 0;
    pkg->buffer = NULL;
    return pkg;
}

void freePackage(PACKAGE_T* pkg) {
    if (pkg->buffer != NULL)
        free(pkg->buffer);
    delete pkg;    
}

void addItem(PACKAGE_T* pkg, void* data, uint32_t size) {
    pkg->buffer = realloc(pkg->buffer, pkg->bufferSize + sizeof(uint32_t) + size);
   
    memcpy((char*)pkg->buffer + pkg->bufferSize, &size, sizeof(uint32_t));
    pkg->bufferSize += sizeof(uint32_t);

    memcpy((char*)pkg->buffer + pkg->bufferSize, data, size);
    pkg->bufferSize += size;
}

void* getItem(PACKAGE_T* pkg) {
    uint32_t size;

    memcpy(&size, pkg->buffer, sizeof(uint32_t));

    void* item = malloc(size);

    memcpy(item, (char*)pkg->buffer + sizeof(uint32_t), size);

    uint32_t totalSize = size + sizeof(uint32_t);
    pkg->bufferSize -= totalSize;

    if (pkg->bufferSize == 0) {
        memmove(pkg->buffer, (char*)pkg->buffer + totalSize, pkg->bufferSize);
        pkg->buffer = realloc(pkg->buffer, pkg->bufferSize);
    } else {
        free(pkg->buffer);
        pkg->buffer = NULL;
    }

    return item;
}

void* serializePackage(PACKAGE_T* pkg) {
    uint32_t totalSize = sizeof(CODE_CONTENT) + sizeof(uint32_t) + pkg->bufferSize;
    void* sPkg = malloc(totalSize + sizeof(uint32_t));
    memcpy(sPkg, &totalSize, sizeof(uint32_t));
    memcpy((char*)sPkg + sizeof(uint32_t), &pkg->code, sizeof(CODE_CONTENT));
    memcpy((char*)sPkg + sizeof(uint32_t) + sizeof(CODE_CONTENT), &pkg->bufferSize, sizeof(uint32_t));
    if (pkg->bufferSize > 0) {
        memcpy((char*)sPkg + sizeof(CODE_CONTENT) + 2 * sizeof(uint32_t), pkg->buffer, pkg->bufferSize);
    }
    
    return sPkg;
}

PACKAGE_T* deserializePackage(void* sPkg) {
    CODE_CONTENT code;
    
    memcpy(&code, sPkg, sizeof(CODE_CONTENT));
    PACKAGE_T* pkg = createPackage(code);

    memcpy(&pkg->bufferSize, (char*)sPkg + sizeof(CODE_CONTENT), sizeof(uint32_t));

    if (pkg->bufferSize > 0) {   
        pkg->buffer = malloc(pkg->bufferSize);
        memcpy(pkg->buffer, (char*)sPkg + sizeof(CODE_CONTENT) + sizeof(uint32_t), pkg->bufferSize);
    }

    return pkg;
}