#ifndef CONFIG_CONTROLLER_H
#define CONFIG_CONTROLLER_H

#include "WidgetController.h"
#include "Widget/config_widget.h"

class ConfigController : public WidgetController {
private:
    void setupConnections() override;

    void onBackRequested(); 
    void onSaveRequested(CONFIG_D newConf); 
public:
    ConfigController(
        LOG_T& logger,
        AppController& appController,
        QWidget* previousWidget
    );

    ~ConfigController ();
};


#endif