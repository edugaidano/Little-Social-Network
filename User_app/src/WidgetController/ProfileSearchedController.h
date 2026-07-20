#ifndef PROFILE_SEARCHED_CONTROLLER_H
#define PROFILE_SEARCHED_CONTROLLER_H

#include <string>
#include "WidgetController.h"
#include "SearchProfileController.h"
#include "../widgets/profile/profile_widget.h"

class ProfileSearchedController : public WidgetController {
private:
    SearchProfileController& searchController;    

    void setupConnections() override;

    std::optional<std::string> getContent(std::string& username);

    void onBackRequested();
    void onContinueSearchingRequested();
public:
    ProfileSearchedController(
        LOG_T& logger,
        AppController& appController,
        SearchProfileController& searchController,
        std::string username,
        QWidget* previousWidget
    );
    ~ProfileSearchedController();
};

#endif