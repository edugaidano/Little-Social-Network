#include "../user_manager.h"
#include <vector>

int deleteMessage(ThreadData* data, PACKAGE_T* pkg) {
    char* username = (char*)getItem(pkg);
    ID_T userId = data->index->findUser(username);
    free(username);

    bool noProblems = true;
    if (userId == 0) {
        noProblems = false;
    } else {   
        auto mutexPtr = messagesMutexManager.getMutex(userId);
        std::lock_guard<std::mutex> lock(*mutexPtr);

        std::vector<MESSAGE_ITEM> buffer;
        std::filesystem::path userMessagesDirPath = storagePath / MESSAGES_DIR / std::to_string(userId);
        
        uint32_t* messageId = (uint32_t*)getItem(pkg);
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

    PACKAGE_T* pkgReply = createPackage(DELETE_MESSAGE_REPLY);
    if (noProblems) {
        addItem(pkgReply, (void*)"OK", 3);
    } else {
        addItem(pkgReply, (void*)"Not OK", 7);
    }
    int retVal = sendPackage(*data->logger, data->clientSocket, pkgReply);
    freePackage(pkgReply);
    return retVal;
}