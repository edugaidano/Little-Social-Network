#ifndef SEARCH_PROFILE_CONTROLLER_H
#define SEARCH_PROFILE_CONTROLLER_H

#include "WidgetController.h"
#include "Widget/SearchProfileWidget.h"

class SearchProfileController : public WidgetController {
private:
    void setupConnections() override;

    void onSearchRequested(QString username);
public:
    SearchProfileController(
        LOG_T& logger,
        AppController& appController, 
        QWidget* previousWidget
    );
    ~SearchProfileController();

    void onBackRequested();
};


#endif