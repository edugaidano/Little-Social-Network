#include "start_server/start_server.h"

// on utils folder
#include "logs/logs.h"
#include "config/config.h"
#include "communication/communication.h"

int main (int argc, char *argv[]) {
    CONFIG_D config = get_config_dictionary("config_file.conf");
    LOG_T logger = log_init(level_from_string(config["LOG_LEVEL"]), "Server.log");

    SOCKET listenSocket = startServer(logger, config);
    
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
        
        PACKAGE_T* pkg = recvPackage(logger, clientSocket);
        if (pkg->code != HANDSHAKE) {
            LOG_ERROR(logger, "Package received different to HANDSHAKE");
            closesocket(clientSocket);
            exit(EXIT_FAILURE);
        }

        //TODO: use info of pkg
        freePackage(pkg);
        
        LOG_INFO(logger, "HANDSHAKE received");
        PACKAGE_T* retPkg = createPackage(RESULT_HANDSHAKE);
        addItem(retPkg, (void*)"Todo OK", 8);
        sendPackage(logger, clientSocket, retPkg);
        freePackage(retPkg);


        /*
        pthread_t pthread;
        pthread_create(&pthread, NULL, manage_user, socket);
        pthread_detach(pthread);
        */
    }

    return 0;
}