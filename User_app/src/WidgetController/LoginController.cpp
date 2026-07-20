#include "WidgetController/LoginController.h"
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
    CODE_CONTENT replyCode;
    switch (typeLogin) {
    case LOGIN:
        replyCode = LOGIN_REPLY;
        break;
    case REGISTER:
        replyCode = REGISTER_REPLY;
        break;
    default:
        LOG_ERROR(logger, "typeLogin must be LOGIN or REGISTER");
        return;
    }
       
    appController.startCommunicator();

    PACKAGE_T* pkgLogin = createPackage(typeLogin);
    addItem(pkgLogin, (void*)username.c_str(), username.size() + 1);
    PACKAGE_T* pkgReply = appController.doRequestToServer(pkgLogin, replyCode);
    freePackage(pkgLogin);

    if (pkgReply == NULL)
        return;
    
    char* item = (char*)getItem(pkgReply);
    freePackage(pkgReply);
    if (item != std::string("OK")) {
        LOG_ERROR(logger, "Login refused");
        // TODO: explain why
        DIALOG_ERROR(widget, tr("Login refused"));
        free(item);
        return;
    }

    LOG_INFO(logger, "Login verified");
    free(item);
    new MainMenuController(logger, appController, username); 
    this->deleteLater();
} 