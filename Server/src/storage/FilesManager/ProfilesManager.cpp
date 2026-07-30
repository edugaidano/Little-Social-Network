#include "storage/FilesManager/ProfilesManager.h"
#include <fstream>

ProfilesManager::ProfilesManager(LOG_T& logger, std::string storagePath) 
    : profilesPath(storagePath),
    FilesManager(logger)
{
    profilesPath/=PROFILES_DIR;
}

int ProfilesManager::updateProfile(ID_T userId, std::string newContent) {
    LOG_DEBUG(logger, "Starting ProfilesManager::updateProfile");
    auto mutex = this->getMutex(userId);
    std::lock_guard<std::mutex> lock(*mutex);
    std::ofstream profile(profilesPath / std::to_string(userId));
    
    if (!profile.is_open()){
        LOG_ERROR(logger, "The profile " + std::to_string(userId) + " isn't open");
        return -1;
    }
    
    profile << newContent;
    LOG_INFO(logger, "The profile " + std::to_string(userId) + " is updated");
    return 0;
}

std::optional<std::string> ProfilesManager::getProfileContent(ID_T userId) {
    auto mutexPtr = this->getMutex(userId);
    std::lock_guard<std::mutex> lock(*mutexPtr);

    std::ifstream profile(profilesPath / std::to_string(userId));
    if (!profile.is_open()){
        LOG_ERROR(logger, "The profile " + std::to_string(userId) + " isn't open");
        return std::nullopt;
    }
    
    std::stringstream content;
    content << profile.rdbuf();
    profile.close();

    LOG_INFO(logger, "Profile " + std::to_string(userId) + " content readed");
    return content.str();
}