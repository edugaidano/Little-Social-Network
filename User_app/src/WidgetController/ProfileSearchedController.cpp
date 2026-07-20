#include "ProfileSearchedController.h"

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
    PACKAGE_T* requestPkg = createPackage(SEARCH_PROFILE);
    addItem(requestPkg, (void*)username.c_str(), username.size() + 1);
    PACKAGE_T* replyPkg = appController.doRequestToServer(requestPkg, PROFILE);
    freePackage(requestPkg);

    if (!replyPkg) {
        return std::nullopt;
    }
    
    char* usr = (char*)getItem(replyPkg);

    if (usr == NULL) {
        LOG_INFO(logger, "The user " + username + " does not have a profile");
        freePackage(replyPkg);
        DIALOG_WARNING(
            previousWidget, 
            tr("The user ").append(username).append(tr(" does not have a profile"))
        );
        return std::nullopt;
    }

    if (usr != username) {
        LOG_ERROR(logger, "The profile received is different to the requested profile");
        free(usr);
        freePackage(replyPkg);
        DIALOG_ERROR(
            previousWidget, 
            tr("Something went wrong while receiving the profile.")
        );
        return std::nullopt;
    }

    free(usr);
    char* c = (char*)getItem(replyPkg);
    freePackage(replyPkg);
    std::string content(c);
    free(c);
    return content;
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