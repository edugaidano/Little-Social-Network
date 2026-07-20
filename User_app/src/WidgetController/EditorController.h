#ifndef EDITOR_CONTROLLER_H
#define EDITOR_CONTROLLER_H

#include <string>
#include "WidgetController.h"
#include "OwnProfileController.h"
#include "../widgets/profile_editor/profile_editor_widget.h"

class EditorController : public WidgetController {
private:
    std::string username;
    OwnProfileController& profileController;

    void setupConnections() override;

    void onBackRequested();
    void onSaveRequested(QString profileContent);

public:
    EditorController(
        LOG_T& logger,
        AppController& appController,
        OwnProfileController& profileController,
        std::string username,
        std::string content,
        QWidget* previousWidget
    );
    ~EditorController();
};

#endif