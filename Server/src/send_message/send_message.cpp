#include "send_message.h"

int sendMessage(LOG_T& logger, PACKAGE_T* messagePkg, SOCKET socket, UserIndex index) {
    char* destinatary = (char*)getItem(messagePkg);
    ID_T destinataryId = index.findUser(destinatary);
    free(destinatary);

    bool noProblems = true;
    if (destinataryId == 0) {
        noProblems = false;
    } else {   
        char* date = (char*)getItem(messagePkg);
        char* sender = (char*)getItem(messagePkg);
        char* subject = (char*)getItem(messagePkg);
        char* content = (char*)getItem(messagePkg);
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
    
    PACKAGE_T* pkg = createPackage(SEND_REPLY);
    if (noProblems) {
        addItem(pkg, (void*)"OK", 3);
    } else {
        addItem(pkg, (void*)"Not OK", 7);
    }
    int retVal = sendPackage(logger, socket, pkg);
    freePackage(pkg);
    return retVal;
}