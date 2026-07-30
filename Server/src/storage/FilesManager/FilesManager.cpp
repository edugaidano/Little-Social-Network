#include "storage/FilesManager/FilesManager.h"

std::shared_ptr<std::mutex> FilesManager::getMutex(ID_T id) {
    std::lock_guard<std::mutex> lock(ownMutex);
    auto& weak = mutexMap[id];
    auto shared = weak.lock();
    if (!shared) {
        shared = std::make_shared<std::mutex>();
        weak = shared;
    }
    return shared;
}

void FilesManager::cleanExpired() {
    std::lock_guard<std::mutex> lock(ownMutex);
    for (auto it = mutexMap.begin(); it != mutexMap.end();) {
        if (it->second.expired()) {
            it = mutexMap.erase(it);
        } else {
            ++it;
        }
    }
}