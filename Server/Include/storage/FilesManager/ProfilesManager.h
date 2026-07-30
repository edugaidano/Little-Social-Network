#ifndef PROFILESS_MANAGER_H
#define PROFILESS_MANAGER_H

#include <filesystem>
#include <optional>
#include "storage/storage_values.h"
#include "storage/FilesManager/FilesManager.h"

class ProfilesManager : public FilesManager {
private:
    std::filesystem::path profilesPath; 

    public:
    ProfilesManager(LOG_T& logger, std::string storagePath);

    int updateProfile(ID_T userId, std::string newContent);
    std::optional<std::string> getProfileContent(ID_T userId);
};

#endif