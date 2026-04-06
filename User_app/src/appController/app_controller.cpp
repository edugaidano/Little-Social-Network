#include "app_controller.h"
#include <QVBoxLayout>

AppController::AppController(LOG_T &logger, CONFIG_D &config, QApplication &app, QWidget *parent) :
    QWidget(parent), 
    logger(logger),
    config(config),
    app(app)
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

    setLanguage();

    LOG_DEBUG(logger, "AppController initialized");
}

void AppController::setLanguage() {
    app.removeTranslator(&translator);

    if (translator.load(("app_" + config["LANGUAGE"]).c_str())) {
        app.installTranslator(&translator);
        
    }
}

void AppController::connectionsForLogin() {
    connect(login, &LoginWidget::loginRequested, this, [this](QString user) {
        LOG_DEBUG(logger, "Login requested for user: " + user.toStdString());
        if (!comController) {
            comController = new CommunicationController(logger, config["SERVER_IP"].c_str(), config["SERVER_PORT"].c_str());
        }
        if (comController->loginRequest(user.toStdString()) != 0) {
            return;
        }        
        stack->setCurrentWidget(mainMenu);
    });

    connect(login, &LoginWidget::registerRequested, this, [this](QString user) {
        LOG_DEBUG(logger, "Register requested for user: " + user.toStdString());
        if (!comController) {
            comController = new CommunicationController(logger, config["SERVER_IP"].c_str(), config["SERVER_PORT"].c_str());
        }
        if (comController->registerRequest(user.toStdString()) != 0) {
            return;
        } 
        stack->setCurrentWidget(mainMenu);
    });

    connect(login, &LoginWidget::configRequested, this, [this]() {
        LOG_DEBUG(logger, "Config requested");
        ConfigWidget *configWidget = new ConfigWidget(logger, config);
        stack->addWidget(configWidget);
        stack->setCurrentWidget(configWidget);

        if (comController) {
            delete comController;
            comController = NULL;
        }

        connect(configWidget, &ConfigWidget::backRequested, this, [this, configWidget]() {
            LOG_DEBUG(logger, "Back requested from config");
            setLanguage();
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

        PROFILE_S* p = comController->myProfileRequest();
        if (p == NULL) 
            return;
        
        ProfileWidget *profile = new ProfileWidget(logger, p->username, p->content, tr("Edit Profile"));
        stack->addWidget(profile);
        stack->setCurrentWidget(profile);

        connect(profile, &ProfileWidget::backToMenuRequested, this, [this, p, profile]() {
            free(p->username);
            free(p->content);
            delete p;
            LOG_DEBUG(logger, "Back to menu requested from profile");
            stack->setCurrentWidget(mainMenu);
            stack->removeWidget(profile);
            profile->deleteLater();
        });

        connect(profile, &ProfileWidget::actionRequested, this, [this, p, profile]() {
            LOG_DEBUG(logger, "Action (edit profile) requested");
            ProfileEditorWidget *editor = new ProfileEditorWidget(logger, p->username, p->content);
            free(p->username);
            free(p->content);
            delete p;
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
        stack->setCurrentWidget(messagesInterface);
        connectionsForMessagesInterface(messagesInterface);

        auto msgs = comController->messagesRequest();
        
        for (MESSAGE_ITEM& msg : msgs) {
            messagesInterface->addMessageItem(msg.id, msg.seen, msg.date, msg.sender, msg.subject);
            free(msg.date);
            free(msg.sender);
            free(msg.subject);
        }
        
        messagesInterface->checkMessagesToDisplay();
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
        PROFILE_S* p = comController->searchRequest(username.toStdString());
        if (p == NULL) 
            return;
        
        ProfileWidget *profile = new ProfileWidget(logger, p->username, p->content, tr("Continue Searching"));
        free(p->username);
        free(p->content);
        delete p;            
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
        LOG_DEBUG(logger, "Save profile requested");

        comController->updateRequest(profileContent.toStdString());

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

    connect(messagesInterface, &MessagesInterfaceWidget::messageSelected, this, [this, messagesInterface](const uint32_t messageId) {
        LOG_DEBUG(logger, "Message selected");
        MessageItemWidget* item = messagesInterface->findMessageById(messageId);
        char* content = comController->messageRequest(messageId);
        if (content != NULL) {
            MessageWidget *messageWidget = new MessageWidget(logger, messageId, item->getDate(), item->getSender(), item->getSubject(), content);
            stack->addWidget(messageWidget);
            stack->setCurrentWidget(messageWidget);
            item->markAsSeen();
            
            connectionsForMessage(messagesInterface, messageWidget);
        }
    });
}

void AppController::connectionsForMessage(MessagesInterfaceWidget *messagesInterface, MessageWidget *message) {
    connect(message, &MessageWidget::backButtonClicked, this, [this, messagesInterface, message]() {
        LOG_DEBUG(logger, "Back button clicked on message");
        stack->setCurrentWidget(messagesInterface);
        stack->removeWidget(message);
        message->deleteLater();
    });

    connect(message, &MessageWidget::deleteButtonClicked, this, [this, messagesInterface, message](const uint32_t messageId) {
        LOG_DEBUG(logger, "Delete button clicked on message");
        if (comController->deleteRequest(messageId) == 0) {
            messagesInterface->removeMessage(messageId);
        }
        stack->setCurrentWidget(messagesInterface);
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
        
        comController->sendRequest(destinatary.toStdString(), subject.toStdString(), content.toStdString());

        stack->setCurrentWidget(mainMenu);
        stack->removeWidget(sendMessageWidget);
        sendMessageWidget->deleteLater();
    });
}