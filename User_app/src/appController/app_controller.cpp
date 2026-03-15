#include "app_controller.h"
#include <QVBoxLayout>

AppController::AppController(QWidget *parent)
    : QWidget(parent)
{
    stack = new QStackedWidget();

    login = new LoginWidget();
    mainMenu = new MainMenuWidget();

    stack->addWidget(login);
    stack->addWidget(mainMenu);

    QVBoxLayout *layout = new QVBoxLayout(this);
    layout->addWidget(stack);

    setupConnections();
}

void AppController::setupConnections() {
    connect(login, &LoginWidget::loginRequested, this, [this](QString user) {
        Q_UNUSED(user);
        stack->setCurrentWidget(mainMenu);
    });

    connect(login, &LoginWidget::registerRequested, this, [this](QString user) {
        Q_UNUSED(user);
        stack->setCurrentWidget(mainMenu);
    });

    connect(mainMenu, &MainMenuWidget::logoutRequested, this, [this]() {
        stack->setCurrentWidget(login);
    });

    connect(mainMenu, &MainMenuWidget::searchProfileRequested, this, [this]() {
        SearchWidget *search = new SearchWidget();
        stack->addWidget(search);
        stack->setCurrentWidget(search);

        connect(search, &SearchWidget::backToMainMenu, this, [this, search]() {
            stack->setCurrentWidget(mainMenu);
            stack->removeWidget(search);
            search->deleteLater();
        });

        connect(search, &SearchWidget::searchProfile, this, [this, search](QString username) {
            Q_UNUSED(username);
            QString profileContent = "Profile content goes here."; //TODO: Get the actual profile content from the database
            QString extraAction = "Buscar otro perfil";
            ProfileWidget *profile = new ProfileWidget(username, profileContent, extraAction);
            stack->addWidget(profile);
            stack->setCurrentWidget(profile);

            connect(profile, &ProfileWidget::backToMenuRequested, this, [this, profile]() {
                stack->setCurrentWidget(mainMenu);
                stack->removeWidget(profile);
                profile->deleteLater();
            });
            
            connect(profile, &ProfileWidget::actionRequested, this, [this, profile, search]() {
                stack->setCurrentWidget(search);
                stack->removeWidget(profile);
                profile->deleteLater();
            });
        });
    });

    connect(mainMenu, &MainMenuWidget::viewProfileRequested, this, [this]() {
        QString username = "Username"; //TODO: Get the actual username from the login widget
        QString profileContent = "Profile content goes here."; //TODO: Get the actual profile content from the database
        QString extraAction = "Editar Perfil";
        ProfileWidget *profile = new ProfileWidget(username, profileContent, extraAction);
        stack->addWidget(profile);
        stack->setCurrentWidget(profile);

        connect(profile, &ProfileWidget::backToMenuRequested, this, [this, profile]() {
            stack->setCurrentWidget(mainMenu);
            stack->removeWidget(profile);
            profile->deleteLater();
        });

        connect(profile, &ProfileWidget::actionRequested, this, [this, username, profileContent, profile]() {
            ProfileEditorWidget *editor = new ProfileEditorWidget(username, profileContent);
            stack->removeWidget(profile);
            profile->deleteLater();
            stack->addWidget(editor);
            stack->setCurrentWidget(editor);

            connect(editor, &ProfileEditorWidget::backToMenuRequested, this, [this, editor]() {
                stack->setCurrentWidget(mainMenu);
                stack->removeWidget(editor);
                editor->deleteLater();
            });

            connect(editor, &ProfileEditorWidget::saveProfileRequested, this, [this, editor](QString profileContent) {
                Q_UNUSED(profileContent);
                stack->setCurrentWidget(mainMenu);
                stack->removeWidget(editor);
                editor->deleteLater();
            });
        });
    });

    connect(mainMenu, &MainMenuWidget::viewMessagesRequested, this, [this]() {
        MessagesInterfaceWidget *messagesInterface = new MessagesInterfaceWidget();
        stack->addWidget(messagesInterface);
        //TODO: Get the actual messages from the database
        messagesInterface->addMessageItem(1, false, "2024-06-01", "Alice", "Hello!");
        messagesInterface->addMessageItem(2, true, "2024-06-02", "Bob", "How are you?");
        stack->setCurrentWidget(messagesInterface);

        connect(messagesInterface, &MessagesInterfaceWidget::backToMainMenu, this, [this, messagesInterface]() {
            stack->setCurrentWidget(mainMenu);
            stack->removeWidget(messagesInterface);
            messagesInterface->deleteLater();
        });

        connect(messagesInterface, &MessagesInterfaceWidget::messageSelected, this, [this](const uint32_t messageId) {
            Q_UNUSED(messageId);
            QString date = "2024-06-01"; //TODO: Get the actual date from the database
            QString sender = "Alice"; //TODO: Get the actual sender from the database
            QString subject = "Hello!"; //TODO: Get the actual subject from the database
            QString content = "This is the content of the message."; //TODO: Get the actual
            MessageWidget *messageWidget = new MessageWidget(messageId, date, sender, subject, content);
            stack->addWidget(messageWidget);
            stack->setCurrentWidget(messageWidget);

            connect(messageWidget, &MessageWidget::backButtonClicked, this, [this, messageWidget]() {
                stack->setCurrentIndex(stack->currentIndex() - 1); // Go back to the messages interface
                stack->removeWidget(messageWidget);
                messageWidget->deleteLater();
            });

            connect(messageWidget, &MessageWidget::deleteButtonClicked, this, [this, messageWidget](const uint32_t id) {
                Q_UNUSED(id);
                stack->setCurrentIndex(stack->currentIndex() - 1); // Go back to the messages interface
                stack->removeWidget(messageWidget);
                messageWidget->deleteLater();
            });
        });
    });

    connect(mainMenu, &MainMenuWidget::sendMessageRequested, this, [this]() {
        SendMessageWidget *sendMessageWidget = new SendMessageWidget();
        stack->addWidget(sendMessageWidget);
        stack->setCurrentWidget(sendMessageWidget);

        connect(sendMessageWidget, &SendMessageWidget::cancelMessage, this, [this, sendMessageWidget]() {
            stack->setCurrentWidget(mainMenu);
            stack->removeWidget(sendMessageWidget);
            sendMessageWidget->deleteLater();
        });

        connect(sendMessageWidget, &SendMessageWidget::sendMessage, this, [this, sendMessageWidget](const QString &destinatary, const QString &subject, const QString &content) {
            Q_UNUSED(destinatary);
            Q_UNUSED(subject);
            Q_UNUSED(content);
            stack->setCurrentWidget(mainMenu);
            stack->removeWidget(sendMessageWidget);
            sendMessageWidget->deleteLater();
        });
    });    
}