#include "../ApplicationCoordinator.h"

void ApplicationCoordinator::onMessagesBack(MessagesInterfaceWidget* messages) {
    LOG_DEBUG(logger, "Back to main menu requested from messages interface");
    closeWidget(messages, mainMenu);
}

void ApplicationCoordinator::onMessageSelected(MessagesInterfaceWidget* messages, uint32_t messageId) {
    LOG_DEBUG(logger, "Message selected");
    MessageItemWidget* item = messages->findMessageById(messageId);
    char* content = comController->requestMessageContent(messageId);
    if (content != NULL) {
        MessageWidget *message = openWidget(new MessageWidget(logger, messageId, item->getDate(), item->getSender(), item->getSubject(), content));
        item->markAsSeen();
        
        setupMessageConnections(messages, message);
    }
}

void ApplicationCoordinator::onMessageBack(MessagesInterfaceWidget* messages, MessageWidget* message) {
    LOG_DEBUG(logger, "Back button clicked on message");
    closeWidget(message, messages);
}

void ApplicationCoordinator::onDeleteMessage(MessagesInterfaceWidget* messages, MessageWidget* message, uint32_t messageId) {
    LOG_DEBUG(logger, "Delete button clicked on message");
    if (comController->deleteMessage(messageId) == 0) {
        messages->removeMessage(messageId);
    }
    closeWidget(message, messages);
}