#ifndef MAIN_MENU_CONTROLLER_H
#define MAIN_MENU_CONTROLLER_H

#include "WidgetController.h"
#include "LoginController.h"
#include "SearchProfileController.h"
#include "OwnProfileController.h"
#include "InboxController.h"
#include "MessageEditorController.h"
#include "../widgets/main_menu/main_menu_widget.h"

class MainMenuController : public WidgetController {
private:
    std::string username;

    void setupConnections() override;

    void onLogoutRequested();
    void onSearchProfileRequested();
    void onViewProfileRequested();
    void onViewInboxRequested();
    void onSendMessageRequested();
public:
    MainMenuController(
        LOG_T& logger,
        AppController& appController,
        std::string username,
        QWidget* previousWidget = nullptr
    );
    ~MainMenuController();
};

#endif