#include "communication_controller.h"

CommunicationController::CommunicationController(LOG_T& logger, const char* ip, const char* port) : 
    logger(logger),
    ip(ip),
    port(port),
    username("")
{
    serverConnection = makeConnection(ip, port);
}