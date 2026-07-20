#include "ConfigController.h"

ConfigController::ConfigController (
    LOG_T& logger,
    AppController& appController,
    QWidget* previousWidget
)
    : WidgetController(logger, appController, previousWidget)
{
    widget = new ConfigWidget(logger, appController.getConfig(), previousWidget);
    setupConnections();
    appController.setCurrentWidget(widget);
}

ConfigController::~ConfigController () {
    LOG_DEBUG(logger, "Deleting ConfigController");
    widget->deleteLater();
}

void ConfigController::setupConnections() {
    connect((ConfigWidget*)widget, &ConfigWidget::backRequested, this, &ConfigController::onBackRequested);
    connect((ConfigWidget*)widget, &ConfigWidget::saveRequested, this, &ConfigController::onSaveRequested);
}

void ConfigController::onBackRequested() {
    LOG_DEBUG(logger, "Back requested from config");
    appController.setCurrentWidget(previousWidget);
    appController.removeWidget(widget);
    this->deleteLater();
}

void ConfigController::onSaveRequested(CONFIG_D newConfig) {
    LOG_DEBUG(logger, "Save requested from config");

    appController.setConfig(newConfig);

    auto it = newConfig.find("LOG_LEVEL");
    if (it != newConfig.end()) {
        appController.setLogLevel(level_from_string(it->second));
    }

    LOG_INFO(logger, "Configuration updated");
    appController.setLanguage();
    appController.setCurrentWidget(previousWidget);
    appController.removeWidget(widget);
}