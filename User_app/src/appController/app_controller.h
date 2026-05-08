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

class AppController : public QWidget
{
    Q_OBJECT

public:
    explicit AppController(LOG_T &logger, CONFIG_D &config, QApplication &app, QWidget *parent = nullptr);

private:
    LOG_T &logger;
    CONFIG_D &config;
    QApplication &app;
    QTranslator translator;
    CommunicationController* comController = NULL;

    QStackedWidget *stack;

    LoginWidget*login;
    MainMenuWidget *mainMenu;

    void connectionsForLogin();
    void connectionsForMainMenu();

    void setLanguage();

    void connectionsForSearch(SearchWidget *search);
    void connectionsForOtherProfile(ProfileWidget *profile);
    void connectionsForProfileEditor(ProfileEditorWidget *editor);
    void connectionsForMessagesInterface(MessagesInterfaceWidget *messagesInterface);
    void connectionsForMessage(MessagesInterfaceWidget *messagesInterface, MessageWidget *message);
    void connectionsForSendMessage(SendMessageWidget *sendMessageWidget);
};

#endif