#include "storage/StorageController.h"

StorageController::StorageController(LOG_T& logger, std::string path)
    : logger(logger),
    storagePath(path),
    messagesManager(logger, path),
    profilesManager(logger, path),
    index(this->storagePath)
{
    std::filesystem::create_directories(storagePath / PROFILES_DIR);
    std::filesystem::create_directories(storagePath / MESSAGES_DIR);

    std::filesystem::path indexPath = storagePath / USERS_INDEX;
    if (!std::filesystem::exists(indexPath)) {
        std::ofstream index(indexPath);
    }

    std::filesystem::path nextIdPath = storagePath / NEXT_ID;
    if (!std::filesystem::exists(nextIdPath)) {
        std::ofstream index(nextIdPath);
        index << (ID_T)1;
    }

    this->cleaner = std::thread(&StorageController::cleanExpiredMutexRutine, this);
}

StorageController::~StorageController() {
    stopCleaner = true;

    if (cleaner.joinable())
        cleaner.join();
}

void StorageController::cleanExpiredMutexRutine() {
    while (!stopCleaner) {   
        std::this_thread::sleep_for(std::chrono::minutes(15));
        LOG_DEBUG(logger, "Start to clean expired mutex rutine.");
        profilesManager.cleanExpired();
        messagesManager.cleanExpired();
    }
}

ID_T StorageController::findUser(std::string username) {
    return this->index.findUser(username);
}

ID_T StorageController::registUser(std::string username) {
    return this->index.createUser(username);
}

int StorageController::updateProfile(std::string username, std::string newContent) {
    ID_T userId = this->index.findUser(username);
    if (userId == 0)
        return -1;

    return this->profilesManager.updateProfile(userId, newContent);
}

int StorageController::createMessage(
    std::string destinatary,
    std::string sender,
    std::string date,
    std::string subject,
    std::string content
) {
    ID_T destinataryId = this->index.findUser(destinatary);
    if (destinataryId == 0)
        return -1;
    
    return this->messagesManager.createMessage(destinataryId, sender, date, subject, content);
}

std::optional<std::string> StorageController::getProfileContent(std::string username) {
    ID_T userId = this->index.findUser(username);
    if (userId == 0)
        return std::nullopt;

    return this->profilesManager.getProfileContent(userId); 
}

int StorageController::deleteMessage(std::string username, ID_T messageId) {
    ID_T userId = this->index.findUser(username);
    if (userId == 0)
        return -1;
    
    return this->messagesManager.deleteMessage(userId, messageId);
}

std::optional<std::string> StorageController::getMessageContent(std::string username, ID_T messageId) {
    ID_T userId = this->index.findUser(username);
    if (userId == 0)
        return std::nullopt;

    return this->messagesManager.getMessageContent(userId, messageId); 
}

std::vector<MESSAGE_ITEM> StorageController::getInbox(std::string username) {
    ID_T userId = this->index.findUser(username);
    if (userId == 0)
        return {};
    
    return this->messagesManager.getInbox(userId);
}