#include "WidgetController/SearchProfileController.h"
#include "WidgetController/ProfileSearchedController.h"

SearchProfileController::SearchProfileController(LOG_T& logger, AppController& appController, QWidget* previousWidget) 
    : WidgetController(logger, appController, previousWidget)
{
    widget = new SearchProfileWidget(logger, previousWidget);
    setupConnections();
    appController.setCurrentWidget(widget);
}

SearchProfileController::~SearchProfileController() {
    widget->deleteLater();
}

void SearchProfileController::setupConnections() {
    connect((SearchProfileWidget*)widget, &SearchProfileWidget::backToMainMenu, this, &SearchProfileController::onBackRequested);
    connect((SearchProfileWidget*)widget, &SearchProfileWidget::searchProfile, this, &SearchProfileController::onSearchRequested);
}

void SearchProfileController::onBackRequested() {
    LOG_INFO(logger, "Back requested");
    appController.setCurrentWidget(previousWidget);
    appController.removeWidget(widget);
    this->deleteLater();
}

void SearchProfileController::onSearchRequested(QString username) {
    LOG_INFO(logger, "Search requested");
    new ProfileSearchedController(logger, appController, *this, username.toStdString(), widget);
}