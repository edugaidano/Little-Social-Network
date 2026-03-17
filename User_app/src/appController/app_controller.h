#ifndef APP_CONTROLLER_H
#define APP_CONTROLLER_H

#include <QWidget>
#include <QStackedWidget>

#include "../login/login_widget.h"
#include "../main_menu/main_menu_widget.h"
#include "../profile/profile_widget.h"
#include "../profile_editor/profile_editor_widget.h"
#include "../search/search_widget.h"
#include "../messages_interface/messages_interface_widget.h"
#include "../message/message_widget.h"
#include "../send_message/send_message_widget.h"
#include "../config/config_widget.h"

// on utils folder
#include "logs/logs.h"
#include "config/config.h"

class AppController : public QWidget
{
    Q_OBJECT

public:
    explicit AppController(LOG_T &logger, CONFIG_D &config, QWidget *parent = nullptr);

private:
    LOG_T &logger;
    CONFIG_D &config;

    QStackedWidget *stack;

    LoginWidget*login;
    MainMenuWidget *mainMenu;

    void connectionsForLogin();
    void connectionsForMainMenu();

    void connectionsForSearch(SearchWidget *search);
    void connectionsForOtherProfile(ProfileWidget *profile);
    void connectionsForProfileEditor(ProfileEditorWidget *editor);
    void connectionsForMessagesInterface(MessagesInterfaceWidget *messagesInterface);
    void connectionsForMessage(MessageWidget *message);
    void connectionsForSendMessage(SendMessageWidget *sendMessageWidget);
};

#endif