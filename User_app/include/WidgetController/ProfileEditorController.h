#ifndef PROFILE_EDITOR_CONTROLLER_H
#define PROFILE_EDITOR_CONTROLLER_H

#include <string>
#include "WidgetController.h"
#include "OwnProfileController.h"
#include "Widget/ProfileEditorWidget.h"

class ProfileEditorController : public WidgetController {
private:
    std::string username;
    OwnProfileController& profileController;

    void setupConnections() override;

    void onBackRequested();
    void onSaveRequested(QString profileContent);

public:
    ProfileEditorController(
        LOG_T& logger,
        AppController& appController,
        OwnProfileController& profileController,
        std::string username,
        std::string content,
        QWidget* previousWidget
    );
    ~ProfileEditorController();
};

#endif