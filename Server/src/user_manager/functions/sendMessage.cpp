#include "user_manager.h"

int sendMessage(ThreadData* data, PACKAGE_T* pkg) {
    char* destinatary = (char*)getItem(pkg);
    ID_T destinataryId = data->index->findUser(destinatary);
    free(destinatary);

    bool noProblems = true;
    if (destinataryId == 0) {
        noProblems = false;
    } else { 
        auto mutexPtr = messagesMutexManager.getMutex(destinataryId);
        std::lock_guard<std::mutex> lock(*mutexPtr);

        char* date = (char*)getItem(pkg);
        char* sender = (char*)getItem(pkg);
        char* subject = (char*)getItem(pkg);
        char* content = (char*)getItem(pkg);
        std::ofstream messageIndex(storagePath / MESSAGES_DIR / std::to_string(destinataryId) / MESSAGES_INDEX, std::ios::binary | std::ios::app);
        ID_T messageId = getNextId(storagePath / MESSAGES_DIR / std::to_string(destinataryId));

        if (messageIndex.is_open() && messageId != 0) {
            messageIndex.write(reinterpret_cast<char*>(&messageId), sizeof(ID_T));

            uint8_t seen = 0;
            messageIndex.write(reinterpret_cast<char*>(&seen), sizeof(uint8_t));
            messageIndex.write(date, DATE_SIZE);
            messageIndex.write(sender, SENDER_SIZE);
            messageIndex.write(subject, SUBJECT_SIZE);

            std::ofstream newMessage(storagePath / MESSAGES_DIR / std::to_string(destinataryId) / MESSAGES_DIR / std::to_string(messageId));
            if (newMessage.is_open()) {
                newMessage << content;
            }
        }
        free(date);
        free(sender);
        free(subject);
        free(content);        
    }
    
    PACKAGE_T* pkgReply = createPackage(SEND_REPLY);
    if (noProblems) {
        addItem(pkgReply, (void*)"OK", 3);
    } else {
        addItem(pkgReply, (void*)"Not OK", 7);
    }
    int retVal = sendPackage(*data->logger, data->clientSocket, pkgReply);
    freePackage(pkgReply);
    return retVal;
}