#ifndef STORAGE_CONTROLLER_H
#define STORAGE_CONTROLLER_H

#include <filesystem>
#include <thread>

#include "logs/logs.h"

#include "storage/storage_values.h"
#include "storage/UserIndex.h"
#include "storage/FilesManager/MessagesManager.h"
#include "storage/FilesManager/ProfilesManager.h"

class StorageController {
private:
    LOG_T& logger;
    std::filesystem::path storagePath;
    
    ProfilesManager profilesManager;
    MessagesManager messagesManager;
    
    UserIndex index;

    std::thread cleaner;
    std::atomic<bool> stopCleaner = false;

    void cleanExpiredMutexRutine();
public:
    StorageController(LOG_T& logger, std::string path);
    ~StorageController();

    ID_T findUser(std::string username);
    ID_T registUser(std::string username);

    int updateProfile(std::string username, std::string newContent);
    int deleteMessage(std::string username, ID_T messageId);
    int createMessage(std::string destinatary, std::string sender, std::string date, std::string subject, std::string content);
    
    std::optional<std::string> getProfileContent(std::string username);
    std::optional<std::string> getMessageContent(std::string username, ID_T messageId);
    
    std::vector<MESSAGE_ITEM> getInbox(std::string username);
};

#endif