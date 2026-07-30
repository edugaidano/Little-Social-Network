#include <fstream>
#include "storage/FilesManager/MessagesManager.h"

MessagesManager::MessagesManager(LOG_T& logger, std::string storagePath)
    : messagesPath(storagePath),
    FilesManager(logger)
{
    messagesPath/=MESSAGES_DIR;
}

ID_T MessagesManager::getNextMessageId(ID_T destinataryUserId) {
    LOG_DEBUG(logger, "Getting a new message id for user " + std::to_string(destinataryUserId));
    std::filesystem::path nextIdPath(messagesPath / std::to_string(destinataryUserId) / NEXT_ID);
    
    std::ifstream inFile(nextIdPath);
    if (!inFile.is_open()) {
        LOG_ERROR(logger, "The nextMessageId isn't open for input");
        return 0;
    }
    
    ID_T id;
    inFile >> id;
    inFile.close();
    
    std::ofstream outFile(nextIdPath, std::ios::trunc);
    if (!outFile.is_open()) {
        LOG_ERROR(logger, "The nextMessageId isn't open for output");
        return 0;
    }
    outFile << (id + 1);
    outFile.close();

    LOG_INFO(logger, "Message ID (" + std::to_string(destinataryUserId) + ":" + std::to_string(id) + ") got correctly");
    return id;
}

int MessagesManager::createMessage(
    ID_T destinataryUserId, 
    std::string sender,
    std::string date,
    std::string subject,
    std::string content
) {
    LOG_DEBUG(logger, "Starting MessagesManager::createMessage");
    auto mutexPtr = this->getMutex(destinataryUserId);
    std::lock_guard<std::mutex> lock(*mutexPtr);

    ID_T messageId = this->getNextMessageId(destinataryUserId);
    if (messageId == 0)
        return -1;
    

    int result = this->addToInbox(destinataryUserId, messageId, sender, date, subject);
    if (result != 0)
        return -1;

    return this->saveContent(destinataryUserId, messageId, content);
}

int MessagesManager::addToInbox(
    ID_T destinataryUserId,
    ID_T messageId, 
    std::string sender,
    std::string date,
    std::string subject
) {
    LOG_DEBUG(logger, "Adding the message " + std::to_string(messageId) + " to inbox " + std::to_string(destinataryUserId));
    std::ofstream messageIndex(messagesPath / std::to_string(destinataryUserId) / MESSAGES_INDEX, std::ios::binary | std::ios::app);

    if (!messageIndex.is_open()){
        LOG_ERROR(logger, "The message index isn't open");
        return -1;
    }
    
    uint8_t seen = 0;
    messageIndex.write(reinterpret_cast<char*>(&messageId), sizeof(ID_T));
    messageIndex.write(reinterpret_cast<char*>(&seen), sizeof(uint8_t));
    messageIndex.write(date.c_str(), DATE_SIZE);
    messageIndex.write(sender.c_str(), SENDER_SIZE);
    messageIndex.write(subject.c_str(), SUBJECT_SIZE);

    if (!messageIndex) {
        LOG_ERROR(logger, "Something went wrong at writing the message index of user " + std::to_string(destinataryUserId));
        return -1;
    } else {
        LOG_INFO(logger, "The message " + std::to_string(destinataryUserId) + ":" + std::to_string(messageId) + "is added to index");
        return 0;
    }
}

int MessagesManager::saveContent(ID_T destinataryUserId, ID_T messageId, std::string content) {
    LOG_DEBUG(logger, "Saving the message " + std::to_string(messageId) + " to inbox " + std::to_string(destinataryUserId));
    std::ofstream newMessage(messagesPath / std::to_string(destinataryUserId) / MESSAGES_DIR / std::to_string(messageId));
    if (newMessage.is_open()) {
        newMessage << content;        
        LOG_INFO(logger, "The message content of " + std::to_string(destinataryUserId) + ":" + std::to_string(messageId) + "is saved" );
        return 0;
    }
    LOG_ERROR(logger, "The new message file isn't open");
    this->removeFromInbox(destinataryUserId, messageId);
    return -1;
}

int MessagesManager::deleteMessage(ID_T userId, ID_T messageId) {
    LOG_DEBUG(logger, "Starting MessagesManager::deleteMessage");
    auto mutexPtr = this->getMutex(userId);
    std::lock_guard<std::mutex> lock(*mutexPtr);

    int result = this->removeFromInbox(userId, messageId);
    if (result != 0)
        return -1;

    std::error_code ec;
    bool removed = std::filesystem::remove(messagesPath / std::to_string(userId) / MESSAGES_DIR / std::to_string(messageId), ec);
    if (ec || !removed) {
        LOG_ERROR(logger, "Something went wrong at removing the message content of " + std::to_string(userId) + ":" + std::to_string(messageId));
        return -1;
    }

    LOG_INFO(logger, "Message " +  std::to_string(userId) + ":" + std::to_string(messageId) + " deletd");
    return 0;
}

std::optional<std::string> MessagesManager::getMessageContent(ID_T userId, ID_T messageId) {
    LOG_DEBUG(logger, "Starting MessagesManager::getMessageContent");
    auto mutexPtr = this->getMutex(userId);
    std::lock_guard<std::mutex> lock(*mutexPtr);
    
    std::filesystem::path userMessagesDir = messagesPath / std::to_string(userId);
    std::ifstream message(userMessagesDir / MESSAGES_DIR / std::to_string(messageId));
    if (!message.is_open())  {
        LOG_ERROR(logger, "The message content of " +  std::to_string(userId) + ":" + std::to_string(messageId) + " isn't open");
        return std::nullopt;
    }

    std::stringstream content;
    content << message.rdbuf();
    message.close();
    
    int result = this->markMessageAsSeen(userId, messageId);
    if (result != 0){
        return std::nullopt;
    }

    LOG_INFO(logger, "Message " + std::to_string(userId) + ":" + std::to_string(messageId) + " readed");
    return content.str();
}

std::vector<MESSAGE_ITEM> MessagesManager::getInbox(ID_T userId) {
    LOG_DEBUG(logger, "Starting MessagesManager::getInbox");
    auto mutexPtr = this->getMutex(userId);
    std::lock_guard<std::mutex> lock(*mutexPtr);
    
    std::ifstream index(messagesPath / std::to_string(userId) / MESSAGES_INDEX, std::ios::binary);
    std::vector<MESSAGE_ITEM> inbox;
    while (true) {
        MESSAGE_ITEM item;
        if (!index.read(reinterpret_cast<char*>(&item), sizeof(MESSAGE_ITEM))) break;
        inbox.push_back(item);
    }

    LOG_INFO(logger, std::to_string(inbox.size()) + " message items got from index");
    return inbox;
}

int MessagesManager::markMessageAsSeen(ID_T userId, ID_T messageId) {
    LOG_DEBUG(logger, "Marking message as seen");
    std::fstream file(messagesPath / std::to_string(userId) / MESSAGES_INDEX  , std::ios::binary | std::ios::in | std::ios::out);

    if (!file.is_open()) {
        LOG_ERROR(logger, "The message index isn't open");
        return -1;
    }

    while (true) {
        std::streampos messageStart = file.tellg();

        ID_T id;
        if (!file.read(reinterpret_cast<char*>(&id), sizeof(ID_T))) break;

        std::streampos seenPos = file.tellg();

        uint8_t seen;
        if (!file.read(reinterpret_cast<char*>(&seen), sizeof(uint8_t))) break;

        if (id == messageId) {
            if (seen == 0) {
                file.seekp(seenPos);
                uint8_t newSeen = 1;
                file.write(reinterpret_cast<char*>(&newSeen), sizeof(uint8_t));
                file.flush();
                if (!file) {
                    LOG_ERROR(logger, "Something went wrong at writing the message index");
                    return -1;
                }
            }
            LOG_DEBUG(logger, "Message " + std::to_string(userId) + ":" + std::to_string(messageId) + "marked as seen");
            return 0;
        }
        file.seekg(DATE_SIZE + SENDER_SIZE + SUBJECT_SIZE, std::ios::cur);
    }
    
    LOG_ERROR(logger, "Something went wrong at reading the message index");
    return -1;
}

int MessagesManager::removeFromInbox(ID_T userId, ID_T messageId) {
    LOG_DEBUG(logger, "Removing message from the inbox");
    std::vector<MESSAGE_ITEM> buffer;
    std::filesystem::path inbox = messagesPath / std::to_string(userId) / MESSAGES_INDEX;

    MESSAGE_ITEM temp;

    std::ifstream inFile(inbox, std::ios::binary);
    if (!inFile.is_open()) {
        LOG_ERROR(logger, "The message index isn't open for input");
        return -1;
    }

    bool found = false;
    while (inFile.read(reinterpret_cast<char*>(&temp), sizeof(MESSAGE_ITEM))) {
        if (temp.id != messageId) {
            buffer.push_back(temp);
        } else {
            found = true;
        }
    }
    inFile.close();

    if (!found) {
        LOG_ERROR(logger, "Can't find the messageId on the message index");
        return -1;
    }

    std::ofstream outFile(inbox, std::ios::binary | std::ios::trunc);
    if (!outFile.is_open()) {
        LOG_ERROR(logger, "The message index isn't open for output");
        return -1;
    }

    if (!buffer.empty()) {
        outFile.write(reinterpret_cast<char*>(buffer.data()), buffer.size() * sizeof(MESSAGE_ITEM));
        if (!outFile.good()) {
            LOG_ERROR(logger, "Something went wrong at writing the message index");
            return -1;
        }
    }
    outFile.close();
    LOG_INFO(logger, "Message item of " + std::to_string(userId) + ":" + std::to_string(messageId) + " removed from index");
    return 0;
}