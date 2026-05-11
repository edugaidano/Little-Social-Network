#include "../ApplicationCoordinator.h"

void ApplicationCoordinator::onLogoutRequested() {
    LOG_DEBUG(logger, "Logout requested");
    comController.reset();
    stack->setCurrentWidget(login);
}

void ApplicationCoordinator::onSearchProfileRequested() {
    LOG_DEBUG(logger, "Search profile requested");
    SearchWidget *search = openWidget(new SearchWidget(logger));

    setupSearchConnections(search);
}

void ApplicationCoordinator::onViewProfileRequested() {
    LOG_DEBUG(logger, "View profile requested");

    PROFILE_S* p = comController->searchOwnProfile();
    if (p == NULL) 
        return;
    
    ProfileWidget *profile = openWidget(new ProfileWidget(logger, p->username, p->content, tr("Edit Profile")));

    setupOwnProfileConnections(profile, p);
}

void ApplicationCoordinator::onViewMessagesRequested() {
    LOG_DEBUG(logger, "View messages requested");
    MessagesInterfaceWidget *messagesInterface = openWidget(new MessagesInterfaceWidget(logger));

    setupMessagesConnections(messagesInterface);

    auto msgs = comController->requestMessages();
    
    for (MESSAGE_ITEM& msg : msgs) {
        messagesInterface->addMessageItem(msg.id, msg.seen, msg.date, msg.sender, msg.subject);
        free(msg.date);
        free(msg.sender);
        free(msg.subject);
    }
    
    messagesInterface->checkMessagesToDisplay();
}

void ApplicationCoordinator::onSendMessageRequested() {
    LOG_DEBUG(logger, "Send message requested");
    SendMessageWidget *newMessage = openWidget(new SendMessageWidget(logger));

    setupSendMessageConnections(newMessage);
}