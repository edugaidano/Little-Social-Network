#ifndef SERVER_STORAGE_H
#define SERVER_STORAGE_H

#include <filesystem>
#include <fstream>
#include <string>

constexpr auto PROFILES_DIR = "Profiles";
constexpr auto MESSAGES_DIR = "Messages";
constexpr auto USERS_INDEX = "Users_Index.txt";

void initStorage(std::filesystem::path storagePath);

#endif // SERVER_STORAGE_H