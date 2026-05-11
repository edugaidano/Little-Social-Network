#include "../ApplicationCoordinator.h"

void ApplicationCoordinator::onCancelSendMessage(SendMessageWidget* newMessage)  {
    LOG_DEBUG(logger, "Cancel button clicked on send message");
    closeWidget(newMessage, mainMenu);
}

void ApplicationCoordinator::onSendMessage(SendMessageWidget* newMessage, const QString& destinatary, const QString& subject, const QString& content) {
    LOG_DEBUG(logger, "Send message requested");
    comController->sendMessage(destinatary.toStdString(), subject.toStdString(), content.toStdString());
    closeWidget(newMessage, mainMenu);
}