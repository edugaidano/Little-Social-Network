#ifndef USER_INDEX_H
#define USER_INDEX_H

#include <filesystem>
#include <unordered_map>
#include <mutex>

#include "storage/storage_values.h"

class UserIndex {
private:
    std::filesystem::path& storagePath;
    std::unordered_map<std::string, ID_T> usernameToId;
    std::mutex usersIndexMutex;
    std::mutex createUserMutex;
    
    ID_T findUserInFile(const std::string& username);
    void saveUser(const std::string& username, ID_T id);
    ID_T getNextId();
public:
    UserIndex(std::filesystem::path& storagePath) : storagePath(storagePath) {}
    ID_T findUser(const std::string& username);
    ID_T createUser(const std::string& username);
};

#endif