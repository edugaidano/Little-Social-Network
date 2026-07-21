#include "WidgetController/LoginController.h"
#include "Protocol/login.h"
#include "ProtocolResult/ProtocolNetworkResult.h"
#include "dialog.h"

LoginController::LoginController(
    LOG_T& logger,
    AppController& appController,
    QWidget* previousWidget
) 
    : WidgetController(logger, appController, previousWidget)
{
    widget = new LoginWidget(logger, previousWidget);
    setupConnections();
    appController.setCurrentWidget(widget);
}

LoginController::~LoginController() {
    LOG_DEBUG(logger, "Deleting LoginController");
    widget->deleteLater();
}

void LoginController::setupConnections() {
    connect((LoginWidget*)widget, &LoginWidget::loginRequested, this, &LoginController::onLoginRequested);
    connect((LoginWidget*)widget, &LoginWidget::registerRequested, this, &LoginController::onRegisterRequested);
    connect((LoginWidget*)widget, &LoginWidget::configRequested, this, &LoginController::onConfigRequested);
}

void LoginController::onLoginRequested(QString username) {
    LOG_DEBUG(logger, "Login requested for user: " + username.toStdString());
    loginProcess(username.toStdString(), LOGIN);
}

void LoginController::onRegisterRequested(QString username) {
    LOG_DEBUG(logger, "Register requested for user: " + username.toStdString());
    loginProcess(username.toStdString(), REGISTER);
}

void LoginController::onConfigRequested() {
    LOG_DEBUG(logger, "Config requested");
    new ConfigController(logger, appController, widget);
}

void LoginController::loginProcess(std::string username, CODE_CONTENT typeLogin) { 
    appController.startCommunicator();
    std::unique_ptr<ProtocolResult> result = loginProtocol(logger, appController.getCommunicator(), username, typeLogin);
    if (auto* networkResult = dynamic_cast<ProtocolNetworkResult*>(result.get())) {
        this->ShowError(networkResult->getError());
        return;
    }
    switch (result->getCode()) {
        case ResultCode::OK :
            new MainMenuController(logger, appController, username); 
            this->deleteLater();
            break;
        case ResultCode::REFUSED :
            DIALOG_ERROR(widget, tr("Login refused."));
            break;
        default:
            DIALOG_ERROR(widget, tr("Something went wrong."));
            break;
    }
} 