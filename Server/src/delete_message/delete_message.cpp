#include "delete_message.h"

int deleteMessage(LOG_T& logger, PACKAGE_T* requestPkg, SOCKET socket, UserIndex index) {
    char* username = (char*)getItem(requestPkg);
    ID_T userId = index.findUser(username);
    free(username);

    bool noProblems = true;
    if (userId == 0) {
        noProblems = false;
    } else {   
        std::vector<MESSAGE_ITEM> buffer;
        std::filesystem::path userMessagesDirPath = storagePath / MESSAGES_DIR / std::to_string(userId);
        
        uint32_t* messageId = (uint32_t*)getItem(requestPkg);
        std::ifstream inFile(userMessagesDirPath / MESSAGES_INDEX, std::ios::binary);
        MESSAGE_ITEM temp;
        while (inFile.read(reinterpret_cast<char*>(&temp), sizeof(MESSAGE_ITEM))) {
            if (temp.id != *messageId) {
                buffer.push_back(temp);
            }
        }
        inFile.close();
        
        std::ofstream outFile(userMessagesDirPath / MESSAGES_INDEX, std::ios::binary | std::ios::trunc);
        if (!buffer.empty()) {
            outFile.write(reinterpret_cast<char*>(buffer.data()), buffer.size() * sizeof(MESSAGE_ITEM));
        }
        std::filesystem::remove(userMessagesDirPath / MESSAGES_DIR / std::to_string(*messageId));
        free(messageId);
        outFile.close();
    }

    PACKAGE_T* pkg = createPackage(DELETE_MESSAGE_REPLY);
    if (noProblems) {
        addItem(pkg, (void*)"OK", 3);
    } else {
        addItem(pkg, (void*)"Not OK", 7);
    }
    int retVal = sendPackage(logger, socket, pkg);
    freePackage(pkg);
    return retVal;
}