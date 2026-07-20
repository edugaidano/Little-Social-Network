#include "WidgetController/OwnProfileController.h"
#include "WidgetController/EditorController.h"

OwnProfileController::OwnProfileController(
    LOG_T& logger,
    AppController& appController,
    std::string username,
    QWidget* previousWidget
)
    : WidgetController(logger, appController, previousWidget),
    username(username)
{
    auto c = getContent();
    if (!c.has_value())
        return;

    this->content.assign(c.value());
    widget = new ProfileWidget(logger, username.c_str(), content.c_str(), tr("Edit Profile"), previousWidget);
    setupConnections();
    appController.setCurrentWidget(widget);
}

OwnProfileController::~OwnProfileController() {
    LOG_DEBUG(logger, "Deleting OwnProfileController");
    appController.removeWidget(widget);
    widget->deleteLater();
}

void OwnProfileController::setupConnections() {
    connect((ProfileWidget*)widget, &ProfileWidget::backToMenuRequested, this, &OwnProfileController::onBackRequested);
    connect((ProfileWidget*)widget, &ProfileWidget::actionRequested, this, &OwnProfileController::onEditRequested);
}

std::optional<std::string> OwnProfileController::getContent() {
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

void OwnProfileController::reloadUI() {
    auto c = getContent();
    if (!c.has_value())
        return;

    this->content.assign(c.value());
    ProfileWidget* w = (ProfileWidget*)widget;
    w->reloadContent(content);
}

void OwnProfileController::onBackRequested() {
    LOG_INFO(logger, "Back requested from own profile");
    this->deleteLater();
}

void OwnProfileController::onEditRequested() {
    LOG_INFO(logger, "Edit profile requested from own profile");
    new EditorController(logger, appController, *this, username, content, widget);
}