#include "WidgetController/ProfileSearchedController.h"
#include "Protocol/request_profile.h"
#include "ProtocolResult/ProtocolNetworkResult.h"
#include "ProtocolResult/ProtocolContentResult.h"

ProfileSearchedController::ProfileSearchedController(
    LOG_T& logger,
    AppController& appController,
    SearchProfileController& searchController,
    std::string username,
    QWidget* previousWidget
)
    : WidgetController(logger, appController, previousWidget),
    searchController(searchController)
{
    auto content = getContent(username);
    if (!content.has_value())
        return;

    widget = new ProfileWidget(logger, username.c_str(), content.value().c_str(), tr("Continue Searching"), previousWidget);
    setupConnections();
    appController.setCurrentWidget(widget);
}

ProfileSearchedController::~ProfileSearchedController() {
    LOG_DEBUG(logger, "Deleting ProfileSearchedController");
    appController.removeWidget(widget);
    widget->deleteLater();
}

void ProfileSearchedController::setupConnections() {
    connect((ProfileWidget*)widget, &ProfileWidget::backToMenuRequested, this, &ProfileSearchedController::onBackRequested);
    connect((ProfileWidget*)widget, &ProfileWidget::actionRequested, this, &ProfileSearchedController::onContinueSearchingRequested);
}

std::optional<std::string> ProfileSearchedController::getContent(std::string& username) {
    std::unique_ptr<ProtocolResult> result = requestProfileProtocol(logger, appController.getCommunicator(), username);
    if (auto* networkResult = dynamic_cast<ProtocolNetworkResult*>(result.get())) {
        this->ShowError(networkResult->getError());
        return std::nullopt;
    }
    if (auto* contentResult = dynamic_cast<ProtocolContentResult*>(result.get())) {
        return contentResult->getContent();
    }
    switch (result->getCode()) {
        case ResultCode::NOT_FIND :
            DIALOG_WARNING(
                previousWidget, 
                tr("The user ").append(username).append(tr(" does not have a profile"))
            );
            break;
        default:
            DIALOG_ERROR(previousWidget, tr("Something went wrong."));
            break;
    }
    return std::nullopt;
}

void ProfileSearchedController::onBackRequested() {
    LOG_INFO(logger, "Back requested from a profile searched");
    searchController.onBackRequested();
    this->deleteLater();
}

void ProfileSearchedController::onContinueSearchingRequested() {
    LOG_INFO(logger, "Continue searching requested from a profile searched");
    appController.setCurrentWidget(previousWidget);
    this->deleteLater();
}