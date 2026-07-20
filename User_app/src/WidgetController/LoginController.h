#ifndef LOGIN_CONTROLLER_H
#define LOGIN_CONTROLLER_H

#include "WidgetController.h"
#include "ConfigController.h"
#include "../widgets/login/login_widget.h"
#include "MainMenuController.h"


class LoginController : public WidgetController {
private:
    void setupConnections() override;

    void onLoginRequested(QString username);
    void onRegisterRequested(QString username);
    void onConfigRequested();

    void loginProcess(std::string username, CODE_CONTENT loginType);

public:
    LoginController(
        LOG_T& logger,
        AppController& appController,
        QWidget* previousWidget = nullptr  
    );

    ~LoginController();
};

#endif