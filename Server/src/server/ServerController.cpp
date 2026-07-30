#include <thread>
#include "server/ServerController.h"
#include "storage/StorageController.h"
#include "users/UserManager.h"
#include "config/config.h"

ServerController::ServerController() {
    CONFIG_D config = get_config_dictionary("Server.conf");
    logger = log_init(level_from_string(config["LOG_LEVEL"]), "Server.log");

    storage = new StorageController(logger, config["STORAGE_PATH"]);

    listenSocket = startServer(logger, config["SERVER_PORT"]);
}

ServerController::~ServerController() {
    LOG_DEBUG(logger, "Deleting ServerController");
    closesocket(listenSocket);
    WSACleanup();
    delete storage;
}

void ServerController::manageConnection() {
    SOCKET clientSocket = accept(listenSocket, NULL, NULL);
    if (clientSocket == INVALID_SOCKET) {
        int err = WSAGetLastError();
        LOG_ERROR(logger, "accept() failed with error: " + std::to_string(err));
        return;
    }

    LOG_INFO(logger, "new connection acepted");

    std::thread thread([this, clientSocket]() {
        UserManager usrManager(logger, *storage, clientSocket);
        usrManager.manageUser();
    });
    thread.detach();
}