#ifndef SERVER_STORAGE_H
#define SERVER_STORAGE_H

#include <filesystem>
#include <fstream>
#include <string>
#include <unordered_map>

constexpr auto PROFILES_DIR = "Profiles";
constexpr auto MESSAGES_DIR = "Messages";
constexpr auto USERS_INDEX = "Users_Index.txt";
constexpr auto NEXT_ID = "Next_ID.txt";

typedef uint32_t UserId_t;

extern std::filesystem::path storagePath;

void initStorage(std::filesystem::path path);

//Required to initStorage() or define the storagePath
class UserIndex {
private:
    std::unordered_map<std::string, UserId_t> usernameToId;
    
    UserId_t findUserInFile(const std::string& username);
    void saveUser(const std::string& username, UserId_t id);
    UserId_t getNextId();
public:
    UserId_t findUser(const std::string& username);
    UserId_t createUser(const std::string& username);
};

#endif // SERVER_STORAGE_H