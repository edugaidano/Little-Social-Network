#include "WidgetController/ProfileEditorController.h"
#include "Protocol/update_profile.h"
#include "ProtocolResult/ProtocolNetworkResult.h"

ProfileEditorController::ProfileEditorController(
    LOG_T& logger,
    AppController& appController,
    OwnProfileController& profileController,
    std::string username,
    std::string content,
    QWidget* previousWidget
)
    : WidgetController(logger, appController, previousWidget),
    profileController(profileController),
    username(username)
{
    widget = new ProfileEditorWidget(logger, username.c_str(), content.c_str(), previousWidget);
    setupConnections();
    appController.setCurrentWidget(widget);   
}

ProfileEditorController::~ProfileEditorController() {
    LOG_DEBUG(logger, "Deleting ProfileEditorController");
    appController.removeWidget(widget);
    widget->deleteLater();
}

void ProfileEditorController::setupConnections() {
    connect((ProfileEditorWidget*)widget, &ProfileEditorWidget::backToMenuRequested, this, &ProfileEditorController::onBackRequested);
    connect((ProfileEditorWidget*)widget, &ProfileEditorWidget::saveProfileRequested, this, &ProfileEditorController::onSaveRequested);
}

void ProfileEditorController::onBackRequested() {
    LOG_INFO(logger, "Back requested");
    appController.setCurrentWidget(previousWidget);
    this->deleteLater();
}

void ProfileEditorController::onSaveRequested(QString profileContent) {
    LOG_INFO(logger, "Save requested");

    std::string content(profileContent.toStdString());
    std::unique_ptr<ProtocolResult> result = updateProfileProtocol(logger, appController.getCommunicator(), username, content);
    if (auto* networkResult = dynamic_cast<ProtocolNetworkResult*>(result.get())) {
        this->ShowError(networkResult->getError());
        return;
    }
    switch (result->getCode()) {
        case ResultCode::OK :
            DIALOG_INFO(widget, tr("Profile updated"));
            break;
        default:
            DIALOG_ERROR(widget, tr("Something went wrong."));
            break;
    }   
    
    profileController.reloadUI();
    appController.setCurrentWidget(previousWidget);
    this->deleteLater();
}