#ifndef APP_CONTROLLER_H
#define APP_CONTROLLER_H

#include <QApplication>
#include <QTranslator>
#include <QWidget>
#include <QStackedWidget>

// Widgets
#include "../widgets/login/login_widget.h"
#include "../widgets/main_menu/main_menu_widget.h"
#include "../widgets/profile/profile_widget.h"
#include "../widgets/profile_editor/profile_editor_widget.h"
#include "../widgets/search/search_widget.h"
#include "../widgets/messages_interface/messages_interface_widget.h"
#include "../widgets/message/message_widget.h"
#include "../widgets/send_message/send_message_widget.h"
#include "../widgets/config/config_widget.h"

// Comunication
#include "../communicationController/communication_controller.h"

// Utils -> on utils folder
#include "logs/logs.h"
#include "config/config.h"

class ApplicationCoordinator : public QWidget
{
    Q_OBJECT

public:
    explicit ApplicationCoordinator(LOG_T &logger, CONFIG_D &config, QApplication &app, QWidget *parent = nullptr);

private:
    LOG_T &logger;
    CONFIG_D &config;
    QApplication &app;
    QTranslator translator;
    
    std::unique_ptr<CommunicationController> comController;;

    QStackedWidget *stack;

    LoginWidget*login;
    MainMenuWidget *mainMenu;

    // core

    template<typename T>
    T* openWidget(T* widget);
    void closeWidget(QWidget* current, QWidget* backTo);
    void destroyWidget(QWidget* widget);

    void setLanguage();

    // connections

    void setupLoginConnections();
    void setupConfigConnections(ConfigWidget* config);

    void setupMainMenuConnections();
    void setupOwnProfileConnections(ProfileWidget* profile, PROFILE_S* p);
    void setupSearchConnections(SearchWidget* search);
    void setupMessagesConnections(MessagesInterfaceWidget* messages);
    void setupSendMessageConnections(SendMessageWidget* newMessage);

    void setupSearchedProfileConnections(ProfileWidget* profile, SearchWidget* search);

    void setupProfileEditorConnections(ProfileEditorWidget* editor);

    void setupMessageConnections(MessagesInterfaceWidget* messages, MessageWidget* message);

    // login flow
    
    void onLoginRequested(QString user);
    void onRegisterRequested(QString user);
    void onConfigRequested();

    // Main menu flow

    void onLogoutRequested();
    void onSearchProfileRequested();
    void onViewProfileRequested();
    void onViewMessagesRequested();
    void onSendMessageRequested();

    // Search flow

    void onSearchBack(SearchWidget* search);
    void onSearchProfile(SearchWidget* search, QString username);

    // Profile flow

    void onProfileBack(ProfileWidget* profile);

    void onContinueSearching(ProfileWidget* profile, SearchWidget* search);
    void onEditProfileRequested(ProfileWidget* profile, PROFILE_S* p);

    void onProfileEditorBack(ProfileEditorWidget* editor);
    void onSaveProfile(ProfileEditorWidget* editor, QString content);

    // Messages flow

    void onMessagesBack(MessagesInterfaceWidget* messages);
    void onMessageSelected(MessagesInterfaceWidget* messages, uint32_t messageId);
    
    void onMessageBack(MessagesInterfaceWidget* messages, MessageWidget* message);
    void onDeleteMessage(MessagesInterfaceWidget* messages, MessageWidget* message, uint32_t messageId);

    // Send message flow

    void onCancelSendMessage(SendMessageWidget* widget);
    void onSendMessage(SendMessageWidget* widget, const QString& destinatary, const QString& subject, const QString& content);
};

template<typename T>
T* ApplicationCoordinator::openWidget(T* widget) {
    stack->addWidget(widget);
    stack->setCurrentWidget(widget);
    return widget;
}

#endif