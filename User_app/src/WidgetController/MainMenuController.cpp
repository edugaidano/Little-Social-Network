#include "WidgetController/MainMenuController.h"

MainMenuController::MainMenuController (
    LOG_T& logger,
    AppController& appController,
    std::string username,
    QWidget* previousWidget
) 
    : WidgetController(logger, appController, previousWidget),
    username(username)
{
    widget = new MainMenuWidget(logger, previousWidget);
    setupConnections();
    appController.setCurrentWidget(widget);
}

MainMenuController::~MainMenuController() {
    LOG_DEBUG(logger, "Deleting MainMenuController");
    widget->deleteLater();
}

void MainMenuController::setupConnections() {
    connect((MainMenuWidget*)widget, &MainMenuWidget::logoutRequested, this, &MainMenuController::onLogoutRequested);
    connect((MainMenuWidget*)widget, &MainMenuWidget::viewProfileRequested, this, &MainMenuController::onViewProfileRequested);
    connect((MainMenuWidget*)widget, &MainMenuWidget::searchProfileRequested, this, &MainMenuController::onSearchProfileRequested);
    connect((MainMenuWidget*)widget, &MainMenuWidget::viewMessagesRequested, this, &MainMenuController::onViewInboxRequested);
    connect((MainMenuWidget*)widget, &MainMenuWidget::sendMessageRequested, this, &MainMenuController::onSendMessageRequested);
}

void MainMenuController::onLogoutRequested() {
    LOG_INFO(logger, "Logout requested");
    new LoginController(logger, appController);
    appController.removeWidget(widget);
    this->deleteLater();
}

void MainMenuController::onSearchProfileRequested() {
    LOG_INFO(logger, "Search profile requested");
    new SearchProfileController(logger, appController, widget);
}

void MainMenuController::onViewProfileRequested() {
    LOG_INFO(logger, "View profile requested");
    new OwnProfileController(logger, appController, username, widget); 
}

void MainMenuController::onViewInboxRequested() {
    LOG_INFO(logger, "View inbox requested");
    new InboxController(logger, appController, username, widget);
}

void MainMenuController::onSendMessageRequested() {
    LOG_INFO(logger, "Send message requested");
    new MessageEditorController(logger, appController, username, widget);
}