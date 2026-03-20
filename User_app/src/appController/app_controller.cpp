#include "app_controller.h"
#include <QVBoxLayout>

AppController::AppController(LOG_T &logger, CONFIG_D &config, QWidget *parent) :
    QWidget(parent), 
    logger(logger),
    config(config)
{
    stack = new QStackedWidget();

    login = new LoginWidget(logger);
    mainMenu = new MainMenuWidget(logger);

    stack->addWidget(login);
    stack->addWidget(mainMenu);

    QVBoxLayout *layout = new QVBoxLayout(this);
    layout->addWidget(stack);

    connectionsForLogin();
    connectionsForMainMenu();
    
    LOG_DEBUG(logger, "AppController initialized");
}

void AppController::connectionsForLogin() {
    connect(login, &LoginWidget::loginRequested, this, [this](QString user) {
        Q_UNUSED(user);
        LOG_DEBUG(logger, "Login requested for user: " + user.toStdString());
        if (!comController) {
            comController = new CommunicationController(logger, config["SERVER_IP"].c_str(), config["SERVER_PORT"].c_str());
        }
        
        stack->setCurrentWidget(mainMenu);
    });

    connect(login, &LoginWidget::registerRequested, this, [this](QString user) {
        Q_UNUSED(user);
        LOG_DEBUG(logger, "Register requested for user: " + user.toStdString());
        if (!comController) {
            comController = new CommunicationController(logger, config["SERVER_IP"].c_str(), config["SERVER_PORT"].c_str());
        }
        stack->setCurrentWidget(mainMenu);
    });

    connect(login, &LoginWidget::configRequested, this, [this]() {
        LOG_DEBUG(logger, "Config requested");
        ConfigWidget *configWidget = new ConfigWidget(logger, config);
        stack->addWidget(configWidget);
        stack->setCurrentWidget(configWidget);

        connect(configWidget, &ConfigWidget::backRequested, this, [this, configWidget]() {
            LOG_DEBUG(logger, "Back requested from config");
            stack->setCurrentWidget(login);
            stack->removeWidget(configWidget);
            configWidget->deleteLater();
        });
    });
}

void AppController::connectionsForMainMenu() {
    connect(mainMenu, &MainMenuWidget::logoutRequested, this, [this]() {
        LOG_DEBUG(logger, "Logout requested");
        if (comController) {
            delete comController;
            comController = NULL;
        }
        
        stack->setCurrentWidget(login);
    });

    connect(mainMenu, &MainMenuWidget::searchProfileRequested, this, [this]() {
        LOG_DEBUG(logger, "Search profile requested");
        SearchWidget *search = new SearchWidget(logger);
        stack->addWidget(search);
        stack->setCurrentWidget(search);

        connectionsForSearch(search);
    });

    connect(mainMenu, &MainMenuWidget::viewProfileRequested, this, [this]() {
        LOG_DEBUG(logger, "View profile requested");
        QString username = "Username"; //TODO: Get the actual username from the login widget
        QString profileContent = "Profile content goes here."; //TODO: Get the actual profile content from the database
        QString extraAction = "Editar Perfil";
        ProfileWidget *profile = new ProfileWidget(logger, username, profileContent, extraAction);
        stack->addWidget(profile);
        stack->setCurrentWidget(profile);

        connect(profile, &ProfileWidget::backToMenuRequested, this, [this, profile]() {
            LOG_DEBUG(logger, "Back to menu requested from profile");
            stack->setCurrentWidget(mainMenu);
            stack->removeWidget(profile);
            profile->deleteLater();
        });

        connect(profile, &ProfileWidget::actionRequested, this, [this, username, profileContent, profile]() {
            LOG_DEBUG(logger, "Action (edit profile) requested");
            ProfileEditorWidget *editor = new ProfileEditorWidget(logger, username, profileContent);
            stack->removeWidget(profile);
            profile->deleteLater();
            stack->addWidget(editor);
            stack->setCurrentWidget(editor);

            connectionsForProfileEditor(editor);
        });
    });

    connect(mainMenu, &MainMenuWidget::viewMessagesRequested, this, [this]() {
        LOG_DEBUG(logger, "View messages requested");
        MessagesInterfaceWidget *messagesInterface = new MessagesInterfaceWidget(logger);
        stack->addWidget(messagesInterface);
        //TODO: Get the actual messages from the database
        messagesInterface->addMessageItem(1, false, "2024-06-01", "Alice", "Hello!");
        messagesInterface->addMessageItem(2, true, "2024-06-02", "Bob", "How are you?");
        stack->setCurrentWidget(messagesInterface);

        connectionsForMessagesInterface(messagesInterface);
    });

    connect(mainMenu, &MainMenuWidget::sendMessageRequested, this, [this]() {
        LOG_DEBUG(logger, "Send message requested");
        SendMessageWidget *sendMessageWidget = new SendMessageWidget(logger);
        stack->addWidget(sendMessageWidget);
        stack->setCurrentWidget(sendMessageWidget);

        connectionsForSendMessage(sendMessageWidget);
    });    
}

void AppController::connectionsForSearch(SearchWidget *search) {
    connect(search, &SearchWidget::backToMainMenu, this, [this, search]() {
        LOG_DEBUG(logger, "Back to main menu requested from search");
        stack->setCurrentWidget(mainMenu);
        stack->removeWidget(search);
        search->deleteLater();
    });

    connect(search, &SearchWidget::searchProfile, this, [this, search](QString username) {
        LOG_DEBUG(logger, "Search profile requested for user: " + username.toStdString());
        Q_UNUSED(username);
        QString profileContent = "Profile content goes here."; //TODO: Get the actual profile content from the database
        QString extraAction = "Buscar otro perfil";
        ProfileWidget *profile = new ProfileWidget(logger, username, profileContent, extraAction);
        stack->addWidget(profile);
        stack->setCurrentWidget(profile);

       connectionsForOtherProfile(profile);
    });

}

void AppController::connectionsForOtherProfile(ProfileWidget *profile) {
    connect(profile, &ProfileWidget::backToMenuRequested, this, [this, profile]() {
        LOG_DEBUG(logger, "Back to menu requested from other profile");
        stack->setCurrentWidget(mainMenu);
        stack->removeWidget(profile);
        profile->deleteLater();
    });
    
    connect(profile, &ProfileWidget::actionRequested, this, [this, profile]() {
        LOG_DEBUG(logger, "Action (search another profile) requested");
        stack->setCurrentIndex(stack->currentIndex() - 1); // Go back to the search widget
        stack->removeWidget(profile);
        profile->deleteLater();
    });
}

void AppController::connectionsForProfileEditor(ProfileEditorWidget *editor) {
    connect(editor, &ProfileEditorWidget::backToMenuRequested, this, [this, editor]() {
        LOG_DEBUG(logger, "Back to menu requested from profile editor");
        stack->setCurrentWidget(mainMenu);
        stack->removeWidget(editor);
        editor->deleteLater();
    });

    connect(editor, &ProfileEditorWidget::saveProfileRequested, this, [this, editor](QString profileContent) {
        Q_UNUSED(profileContent);
        LOG_DEBUG(logger, "Save profile requested");
        stack->setCurrentWidget(mainMenu);
        stack->removeWidget(editor);
        editor->deleteLater();
    });
}

void AppController::connectionsForMessagesInterface(MessagesInterfaceWidget *messagesInterface) {
    connect(messagesInterface, &MessagesInterfaceWidget::backToMainMenu, this, [this, messagesInterface]() {
        LOG_DEBUG(logger, "Back to main menu requested from messages interface");
        stack->setCurrentWidget(mainMenu);
        stack->removeWidget(messagesInterface);
        messagesInterface->deleteLater();
    });

    connect(messagesInterface, &MessagesInterfaceWidget::messageSelected, this, [this](const uint32_t messageId) {
        LOG_DEBUG(logger, "Message selected");
        QString date = "2024-06-01"; //TODO: Get the actual date from the database
        QString sender = "Alice"; //TODO: Get the actual sender from the database
        QString subject = "Hello!"; //TODO: Get the actual subject from the database
        QString content = "This is the content of the message."; //TODO: Get the actual content from the database
        MessageWidget *messageWidget = new MessageWidget(logger, messageId, date, sender, subject, content);
        stack->addWidget(messageWidget);
        stack->setCurrentWidget(messageWidget);

        connectionsForMessage(messageWidget);
    });
}

void AppController::connectionsForMessage(MessageWidget *message) {
    connect(message, &MessageWidget::backButtonClicked, this, [this, message]() {
        LOG_DEBUG(logger, "Back button clicked on message");
        stack->setCurrentIndex(stack->currentIndex() - 1); // Go back to the messages interface
        stack->removeWidget(message);
        message->deleteLater();
    });

    connect(message, &MessageWidget::deleteButtonClicked, this, [this, message](const uint32_t id) {
        LOG_DEBUG(logger, "Delete button clicked on message");
        Q_UNUSED(id);
        stack->setCurrentIndex(stack->currentIndex() - 1); // Go back to the messages interface
        stack->removeWidget(message);
        message->deleteLater();
    });
}

void AppController::connectionsForSendMessage(SendMessageWidget *sendMessageWidget) {
    connect(sendMessageWidget, &SendMessageWidget::cancelMessage, this, [this, sendMessageWidget]() {
        LOG_DEBUG(logger, "Cancel button clicked on send message");
        stack->setCurrentWidget(mainMenu);
        stack->removeWidget(sendMessageWidget);
        sendMessageWidget->deleteLater();
    });

    connect(sendMessageWidget, &SendMessageWidget::sendMessage, this, [this, sendMessageWidget](const QString &destinatary, const QString &subject, const QString &content) {
        LOG_DEBUG(logger, "Send message requested");
        Q_UNUSED(destinatary);
        Q_UNUSED(subject);
        Q_UNUSED(content);
        stack->setCurrentWidget(mainMenu);
        stack->removeWidget(sendMessageWidget);
        sendMessageWidget->deleteLater();
    });
}