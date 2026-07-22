#include "start_server/start_server.h"
#include "user_manager/user_manager.h"
#include "server_storage/server_storage.h"

// on Global folder
#include "config/config.h"

int main (int argc, char *argv[]) {
    CONFIG_D config = get_config_dictionary("Server.conf");
    LOG_T logger = log_init(level_from_string(config["LOG_LEVEL"]), "Server.log");
    
    initStorage(config["STORAGE_PATH"]);
    
    UserIndex index;

    SOCKET listenSocket = startServer(logger, config["SERVER_PORT"]);
    
    while (true) {
        SOCKET clientSocket = accept(listenSocket, NULL, NULL);
        if (clientSocket == INVALID_SOCKET) {
            int err = WSAGetLastError();
            LOG_ERROR(logger, "accept() failed with error: " + std::to_string(err));
            closesocket(listenSocket);
            WSACleanup();
            return 1;
        }   

        LOG_DEBUG(logger, "new connection acepted");
        ThreadData* data = new ThreadData{clientSocket, &logger, &index};

        pthread_t pthread;
        pthread_create(&pthread, NULL, userManager, data);
        pthread_detach(pthread);
    }

    return 0;
}