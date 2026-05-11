#include "../ApplicationCoordinator.h"

void ApplicationCoordinator::onLoginRequested(QString user) {
    LOG_DEBUG(logger, "Login requested for user: " + user.toStdString());
    comController = std::make_unique<CommunicationController>(logger, config["SERVER_IP"].c_str(), config["SERVER_PORT"].c_str());
    if (comController->login(user.toStdString(), LOGIN) != 0) {
        return;
    }        
    stack->setCurrentWidget(mainMenu);
}

void ApplicationCoordinator::onRegisterRequested(QString user) {
    LOG_DEBUG(logger, "Register requested for user: " + user.toStdString());
    comController = std::make_unique<CommunicationController>(logger, config["SERVER_IP"].c_str(), config["SERVER_PORT"].c_str());
    if (comController->login(user.toStdString(), REGISTER) != 0) {
        return;
    } 
    stack->setCurrentWidget(mainMenu);
}

void ApplicationCoordinator::onConfigRequested() {
    LOG_DEBUG(logger, "Config requested");
    ConfigWidget *configWidget = openWidget(new ConfigWidget(logger, config));

    comController.reset();

    setupConfigConnections(configWidget);
}