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
constexpr auto MESSAGES_INDEX = "Messages_Index";

typedef uint32_t ID_T;

#define DATE_SIZE 15
#define SENDER_SIZE 31
#define SUBJECT_SIZE 101

typedef struct MESSAGE_ITEM {
    ID_T id;
    uint8_t seen;
    char date[DATE_SIZE];
    char sender[SENDER_SIZE];
    char subject[SUBJECT_SIZE];
} MESSAGE_ITEM;

extern std::filesystem::path storagePath;

void initStorage(std::filesystem::path path);
ID_T getNextId(std::filesystem::path dirPath);

//Required to initStorage() or define the storagePath
class UserIndex {
private:
    std::unordered_map<std::string, ID_T> usernameToId;
    
    ID_T findUserInFile(const std::string& username);
    void saveUser(const std::string& username, ID_T id);
public:
    ID_T findUser(const std::string& username);
    ID_T createUser(const std::string& username);
};

#endif // SERVER_STORAGE_H