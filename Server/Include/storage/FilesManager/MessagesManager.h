#ifndef MESSAGES_MANAGER_H
#define MESSAGES_MANAGER_H

#include <filesystem>
#include <vector>
#include <optional>
#include "storage/storage_values.h"
#include "storage/FilesManager/FilesManager.h"

class MessagesManager : public FilesManager {
private:
    std::filesystem::path messagesPath; 

    ID_T getNextMessageId(ID_T destinataryUserId);
    int saveContent(ID_T destinataryUserId, ID_T messageId, std::string content);
    int addToInbox(ID_T destinataryUserId, ID_T messageId, std::string sender, std::string date, std::string subject);
    int removeFromInbox(ID_T userId, ID_T messageId);
    int markMessageAsSeen(ID_T userId, ID_T messageId);

    public:
    MessagesManager(LOG_T& logger, std::string storagePath);

    int createMessage(
        ID_T destinataryUserId, 
        std::string sender,
        std::string date,
        std::string subject,
        std::string content
    );
    int deleteMessage(ID_T userId, ID_T messageId);
    std::optional<std::string> getMessageContent(ID_T userId, ID_T messageId);
    std::vector<MESSAGE_ITEM> getInbox(ID_T userId);
};

#endif