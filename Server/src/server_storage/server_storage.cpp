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
        index << (ID_T)1;
    }

    storagePath = path;
}

// Todo: add mutex
ID_T getNextId(std::filesystem::path dirPath) {
    ID_T id = 0;

    std::ifstream inFile(dirPath / NEXT_ID);
    if (inFile.is_open()) {
        inFile >> id;
        inFile.close();
    }

    std::ofstream outFile(dirPath / NEXT_ID, std::ios::trunc);
    outFile << (id + 1);
    outFile.close();

    return id;
}

ID_T UserIndex::findUserInFile(const std::string& username) {
    std::ifstream file(storagePath / USERS_INDEX, std::ios::binary);
    if (!file.is_open()) return 0;

    while (file) {
        uint8_t size;
        file.read(reinterpret_cast<char*>(&size), sizeof(uint8_t));
        if (!file) break;

        std::string fileUsername(size, '\0');
        file.read(&fileUsername[0], size);

        ID_T id;
        file.read(reinterpret_cast<char*>(&id), sizeof(id));

        if (!file) break;

        if (fileUsername == username) {
            return id;
        }
    }

    return 0;
}

ID_T UserIndex::findUser(const std::string& username) {
    auto it = usernameToId.find(username);
    if (it != usernameToId.end()) {
        return it->second;
    }

    ID_T result = findUserInFile(username);
    if (result != 0) {
        usernameToId[username] = result;
    }

    return result;
}

void UserIndex::saveUser(const std::string& username, ID_T id) {
    std::ofstream file(storagePath / USERS_INDEX, std::ios::binary | std::ios::app);

    uint8_t size = username.size();
    file.write(reinterpret_cast<const char*>(&size), sizeof(uint8_t));
    file.write(username.data(), size);
    file.write(reinterpret_cast<const char*>(&id), sizeof(id));
}

ID_T UserIndex::createUser(const std::string& username) {
    if (findUser(username)) {
        return 0;
    }

    ID_T id = getNextId(storagePath);
    if (id != 0) {
        std::ofstream userProfile (storagePath / PROFILES_DIR / std::to_string(id));
        std::filesystem::create_directories(storagePath / MESSAGES_DIR / std::to_string(id) / MESSAGES_DIR);
        std::ofstream userMessages (storagePath / MESSAGES_DIR / std::to_string(id) / MESSAGES_INDEX);
        std::ofstream index (storagePath / MESSAGES_DIR / std::to_string(id) / NEXT_ID, std::ios::binary);
        index << (uint32_t)1;
        usernameToId[username] = id;
        saveUser(username, id);
    }

    return id;
}