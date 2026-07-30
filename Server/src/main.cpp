#include "server/ServerController.h"

int main (int argc, char *argv[]) {
    
    ServerController server;
    
    while (true) {
        server.manageConnection();
    }
    
    return 0;
}