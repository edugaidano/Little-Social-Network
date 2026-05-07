#include "find_message.h"

void markMessageAsSeen(std::filesystem::path path, ID_T targetId);

int findMessage(LOG_T& logger, PACKAGE_T* requestPkg, SOCKET socket, UserIndex index) {
    char* username = (char*)getItem(requestPkg);
    ID_T userId = index.findUser(username);
    free(username);

    PACKAGE_T* pkg = createPackage(MESSAGE);
    if (userId != 0) {
        auto mutexPtr = messagesMutexManager.getMutex(userId);
        std::lock_guard<std::mutex> lock(*mutexPtr);
        
        uint32_t* messageId = (uint32_t*)getItem(requestPkg);
        std::filesystem::path userMessagesDir = storagePath / MESSAGES_DIR / std::to_string(userId);
        std::ifstream message(userMessagesDir / MESSAGES_DIR / std::to_string(*messageId));
        free(messageId);
        if (message.is_open()) {
            std::stringstream content;
            content << message.rdbuf();
            message.close();
            addItem(pkg, (void*)content.str().c_str(), content.str().size() + 1);
        }
        markMessageAsSeen(userMessagesDir / MESSAGES_INDEX, *messageId);
    }
    int retVal = sendPackage(logger, socket, pkg);
    freePackage(pkg);
    return retVal;
}

void markMessageAsSeen(std::filesystem::path path, ID_T targetId) {
    std::fstream file(path, std::ios::binary | std::ios::in | std::ios::out);

    if (!file.is_open()) return;

    while (true) {
        std::streampos messageStart = file.tellg();

        ID_T messageId;
        if (!file.read(reinterpret_cast<char*>(&messageId), sizeof(ID_T))) break;

        std::streampos seenPos = file.tellg();

        uint8_t seen;
        if (!file.read(reinterpret_cast<char*>(&seen), sizeof(uint8_t))) break;

        if (messageId == targetId) {
            file.seekp(seenPos);

            uint8_t newSeen = 1;
            file.write(reinterpret_cast<char*>(&newSeen), sizeof(uint8_t));

            file.flush();
            return;
        }

        file.seekg(DATE_SIZE + SENDER_SIZE + SUBJECT_SIZE, std::ios::cur);
    }
}