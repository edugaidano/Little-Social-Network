#include "server_storage.h"

void initStorage(std::filesystem::path storagePath) {
    std::filesystem::create_directories(storagePath / PROFILES_DIR);
    std::filesystem::create_directories(storagePath / MESSAGES_DIR);

    std::filesystem::path indexPath = storagePath / USERS_INDEX;

    if (!std::filesystem::exists(indexPath)) {
        std::ofstream index(indexPath);
    }
}