#include "server_storage.h"

std::filesystem::path storagePath;

void initStorage(std::filesystem::path path) {
    std::filesystem::create_directories(path / PROFILES_DIR);
    std::filesystem::create_directories(path / MESSAGES_DIR);

    std::filesystem::path indexPath = path / USERS_INDEX;
    if (!std::filesystem::exists(indexPath)) {
        std::ofstream index(indexPath);
    }

    std::filesystem::path nextIdPath = path / NEXT_ID;
    if (!std::filesystem::exists(nextIdPath)) {
        std::ofstream index(nextIdPath);
        index << (UserId_t)1;
    }

    storagePath = path;
}

UserId_t UserIndex::findUserInFile(const std::string& username) {
    std::ifstream file(storagePath / USERS_INDEX);
    if (!file.is_open()) return 0;

    std::string line;
    while (std::getline(file, line)) {
        std::stringstream ss(line);
        std::string fileUsername;
        UserId_t id;

        if (std::getline(ss, fileUsername, ':') && ss >> id) {
            if (fileUsername == username) {
                return id;
            }
        }
    }

    return 0;
}

// Todo: add mutex
UserId_t UserIndex::getNextId() {
    UserId_t id = 0;

    std::ifstream inFile(storagePath / NEXT_ID);
    if (inFile.is_open()) {
        inFile >> id;
        inFile.close();
    }

    std::ofstream outFile(storagePath / NEXT_ID, std::ios::trunc);
    outFile << (id + 1);
    outFile.close();

    return id;
}

UserId_t UserIndex::findUser(const std::string& username) {
    auto it = usernameToId.find(username);
    if (it != usernameToId.end()) {
        return it->second;
    }

    UserId_t result = findUserInFile(username);
    if (result != 0) {
        usernameToId[username] = result;
    }

    return result;
}

void UserIndex::saveUser(const std::string& username, UserId_t id) {
    std::ofstream file(storagePath / USERS_INDEX, std::ios::app);
    file << username << ":" << id << "\n";
}

UserId_t UserIndex::createUser(const std::string& username) {
    if (findUser(username)) {
        return 0;
    }

    UserId_t id = getNextId();
    if (id != 0) {   
        usernameToId[username] = id;
        saveUser(username, id);
    }

    return id;
}