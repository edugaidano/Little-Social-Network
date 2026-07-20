#ifndef OWN_PROFILE_CONTROLLER_H
#define OWN_PROFILE_CONTROLLER_H

#include "WidgetController.h"
#include "Widget/ProfileWidget.h"

class OwnProfileController : public WidgetController {
private:
    std::string username;
    std::string content;
    void setupConnections() override;

    std::optional<std::string> getContent();

    void onBackRequested();
    void onEditRequested();
public:
    OwnProfileController(
        LOG_T& logger,
        AppController& appController,
        std::string username,
        QWidget* previousWidget
    );
    ~OwnProfileController();
    
    void reloadUI();
};


#endif
