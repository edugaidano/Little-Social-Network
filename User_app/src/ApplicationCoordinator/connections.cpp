#include "ApplicationCoordinator.h"

void ApplicationCoordinator::setupLoginConnections() {
    connect(login, &LoginWidget::loginRequested, this, &ApplicationCoordinator::onLoginRequested);
    connect(login, &LoginWidget::registerRequested, this, &ApplicationCoordinator::onRegisterRequested);
    connect(login, &LoginWidget::configRequested, this, &ApplicationCoordinator::onConfigRequested);
}

void ApplicationCoordinator::setupConfigConnections(ConfigWidget* configWidget) {
    connect(configWidget, &ConfigWidget::backRequested, this, 
        [this, configWidget]() {
            LOG_DEBUG(logger, "Back requested from config");
            setLanguage();
            closeWidget(configWidget, login);
        }
    );
}

void ApplicationCoordinator::setupMainMenuConnections() {
    connect(mainMenu, &MainMenuWidget::logoutRequested, this, &ApplicationCoordinator::onLogoutRequested);
    connect(mainMenu, &MainMenuWidget::searchProfileRequested, this, &ApplicationCoordinator::onSearchProfileRequested);
    connect(mainMenu, &MainMenuWidget::viewProfileRequested, this, &ApplicationCoordinator::onViewProfileRequested);
    connect(mainMenu, &MainMenuWidget::viewMessagesRequested, this, &ApplicationCoordinator::onViewMessagesRequested);
    connect(mainMenu, &MainMenuWidget::sendMessageRequested, this, &ApplicationCoordinator::onSendMessageRequested);
}

void ApplicationCoordinator::setupOwnProfileConnections(ProfileWidget* profile, PROFILE_S* p){
    connect(profile, &ProfileWidget::backToMenuRequested, this, 
        [this, profile, p] {
            free(p->username);
            free(p->content);
            delete p;
            onProfileBack(profile);
        }
    );
    connect(profile, &ProfileWidget::actionRequested, this, [this, p, profile]{onEditProfileRequested(profile, p);});
}

void ApplicationCoordinator::setupSearchConnections(SearchWidget *search) {
    connect(search, &SearchWidget::backToMainMenu, this, 
        [this, search] {
            onSearchBack(search);
        }
    );
    connect(search, &SearchWidget::searchProfile, this, 
        [this, search](QString username) {
            onSearchProfile(search, username);
        }
    );
}

void ApplicationCoordinator::setupMessagesConnections(MessagesInterfaceWidget *messages) {
    connect(messages, &MessagesInterfaceWidget::backToMainMenu, this, 
        [this, messages] {
            onMessagesBack(messages);
        }
    );
    connect(messages, &MessagesInterfaceWidget::messageSelected, this, 
        [this, messages](uint32_t mId) {
            onMessageSelected(messages, mId);
        }
    );
}

void ApplicationCoordinator::setupSendMessageConnections(SendMessageWidget* newMessage) {
    connect(newMessage, &SendMessageWidget::cancelMessage, this, 
        [this, newMessage] {
            onCancelSendMessage(newMessage);
        }
    );
    connect(newMessage, &SendMessageWidget::sendMessage, this, 
        [this, newMessage](QString destinatary, QString subject, QString content) {
            onSendMessage(newMessage, destinatary, subject, content);
        }
    );
}

void ApplicationCoordinator::setupSearchedProfileConnections(ProfileWidget *profile, SearchWidget* search) {
    connect(profile, &ProfileWidget::backToMenuRequested, this, 
        [this, profile] {
            onProfileBack(profile);
        }
    );
    connect(profile, &ProfileWidget::actionRequested, this, 
        [this, profile, search] {
            onContinueSearching(profile, search);
        }
    );
}

void ApplicationCoordinator::setupProfileEditorConnections(ProfileEditorWidget* editor) {
    connect(editor, &ProfileEditorWidget::backToMenuRequested, this, 
        [this, editor] {
            onProfileEditorBack(editor);
        }
    );
    connect(editor, &ProfileEditorWidget::saveProfileRequested, this, 
        [this, editor](QString profileContent) {
            onSaveProfile(editor, profileContent);
        }
    );
}

void ApplicationCoordinator::setupMessageConnections(MessagesInterfaceWidget *messages, MessageWidget *message) {
    connect(message, &MessageWidget::backButtonClicked, this, 
        [this, messages, message] {
            onMessageBack(messages, message);
        }
    );
    connect(message, &MessageWidget::deleteButtonClicked, this, 
        [this, messages, message](uint32_t mId) {
            onDeleteMessage(messages, message, mId);
        }
    );
}
