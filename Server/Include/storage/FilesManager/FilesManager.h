#ifndef FILES_MANAGER_H
#define FILES_MANAGER_H

#include <mutex>
#include <unordered_map>
#include <memory>

#include "logs/logs.h" 

#include "storage/storage_values.h"

class FilesManager {
protected:
    LOG_T& logger;
private:
    std::mutex ownMutex;
    std::unordered_map<ID_T, std::weak_ptr<std::mutex>> mutexMap;

public:
    FilesManager(LOG_T& logger) : logger(logger) {};
    std::shared_ptr<std::mutex> getMutex(ID_T id);
    void cleanExpired();
};

#endif