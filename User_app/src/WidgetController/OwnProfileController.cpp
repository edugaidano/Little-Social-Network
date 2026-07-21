#include "WidgetController/OwnProfileController.h"
#include "WidgetController/ProfileEditorController.h"
#include "Protocol/request_profile.h"
#include "ProtocolResult/ProtocolNetworkResult.h"
#include "ProtocolResult/ProtocolContentResult.h"

OwnProfileController::OwnProfileController(
    LOG_T& logger,
    AppController& appController,
    std::string username,
    QWidget* previousWidget
)
    : WidgetController(logger, appController, previousWidget),
    username(username)
{
    auto c = getContent();
    if (!c.has_value())
        return;

    this->content.assign(c.value());
    widget = new ProfileWidget(logger, username.c_str(), content.c_str(), tr("Edit Profile"), previousWidget);
    setupConnections();
    appController.setCurrentWidget(widget);
}

OwnProfileController::~OwnProfileController() {
    LOG_DEBUG(logger, "Deleting OwnProfileController");
    appController.removeWidget(widget);
    widget->deleteLater();
}

void OwnProfileController::setupConnections() {
    connect((ProfileWidget*)widget, &ProfileWidget::backToMenuRequested, this, &OwnProfileController::onBackRequested);
    connect((ProfileWidget*)widget, &ProfileWidget::actionRequested, this, &OwnProfileController::onEditRequested);
}

std::optional<std::string> OwnProfileController::getContent() {
    std::unique_ptr<ProtocolResult> result = requestProfileProtocol(logger, appController.getCommunicator(), username);
    if (auto* networkResult = dynamic_cast<ProtocolNetworkResult*>(result.get())) {
        this->ShowError(networkResult->getError());
        return std::nullopt;
    }
    
    if (auto* contentResult = dynamic_cast<ProtocolContentResult*>(result.get())) {
        return contentResult->getContent();
    }

    DIALOG_ERROR(previousWidget, tr("Something went wrong."));
    return std::nullopt;
}

void OwnProfileController::reloadUI() {
    auto c = getContent();
    if (!c.has_value())
        return;

    this->content.assign(c.value());
    ProfileWidget* w = (ProfileWidget*)widget;
    w->reloadContent(content);
}

void OwnProfileController::onBackRequested() {
    LOG_INFO(logger, "Back requested from own profile");
    this->deleteLater();
}

void OwnProfileController::onEditRequested() {
    LOG_INFO(logger, "Edit profile requested from own profile");
    new ProfileEditorController(logger, appController, *this, username, content, widget);
}