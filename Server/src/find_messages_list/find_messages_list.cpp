#include "find_messages_list.h"

int findMessagesList(LOG_T& logger, PACKAGE_T* requestPkg, SOCKET socket, UserIndex index) {
    char* username = (char*)getItem(requestPkg);
    ID_T userId = index.findUser(username);
    free(username);

    PACKAGE_T* pkg = createPackage(MESSAGES);
    if (userId != 0) {
        std::ifstream index(storagePath / MESSAGES_DIR / std::to_string(userId) / MESSAGES_INDEX, std::ios::binary);
       while (true) {
            MESSAGE_ITEM item;
            if (!index.read(reinterpret_cast<char*>(&item), sizeof(MESSAGE_ITEM))) break;
            addItem(pkg, &item.id, sizeof(ID_T));
            addItem(pkg, &item.seen, sizeof(uint8_t));
            addItem(pkg, item.date, std::string(item.date).size() + 1);
            addItem(pkg, item.sender, std::string(item.sender).size() + 1);
            addItem(pkg, item.subject, std::string(item.subject).size() + 1);
        }
    }
    int retVal = sendPackage(logger, socket, pkg);
    freePackage(pkg);
    return retVal;
}