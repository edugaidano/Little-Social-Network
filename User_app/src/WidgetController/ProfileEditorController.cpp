#include "WidgetController/ProfileEditorController.h"

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

    PACKAGE_T* updatePkg = createPackage(UPDATE_PROFILE);
    addItem(updatePkg, (void*)username.c_str(), username.size() + 1);
    addItem(updatePkg, (void*)profileContent.toStdString().c_str(), profileContent.size() + 1);
    PACKAGE_T* replyPkg = appController.doRequestToServer(updatePkg, UPDATE_REPLY);
    freePackage(updatePkg);

    if (replyPkg == NULL)
        return;

    QString recvErr = tr("Something went wrong while receiving the update reply.");

    char* item = (char*)getItem(replyPkg);
    freePackage(replyPkg);
    if (item == std::string("OK")) {
        LOG_INFO(logger, "Profile updated");
    } else {
        LOG_ERROR(logger, "UPDATE_REPLY item diferent to OK");
        DIALOG_ERROR(nullptr, tr("Something went wrong during the update."));
    }
    free(item);
    
    profileController.reloadUI();
    appController.setCurrentWidget(previousWidget);
    this->deleteLater();
}