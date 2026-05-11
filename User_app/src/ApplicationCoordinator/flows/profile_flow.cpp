#include "../ApplicationCoordinator.h"

void ApplicationCoordinator::onProfileBack(ProfileWidget* profile)  {
    LOG_DEBUG(logger, "Back to menu requested from a profile");
    closeWidget(profile, mainMenu);
}

void ApplicationCoordinator::onContinueSearching(ProfileWidget* profile, SearchWidget* search) {
    LOG_DEBUG(logger, "Action (search another profile) requested");
    closeWidget(profile, search);
}

void ApplicationCoordinator::onEditProfileRequested(ProfileWidget* profile, PROFILE_S* p) {
    LOG_DEBUG(logger, "Action (edit profile) requested");
    ProfileEditorWidget *editor = openWidget(new ProfileEditorWidget(logger, p->username, p->content));
    destroyWidget(profile);
    free(p->username);
    free(p->content);
    delete p;

    setupProfileEditorConnections(editor);
}

void ApplicationCoordinator::onProfileEditorBack(ProfileEditorWidget* editor)  {
    LOG_DEBUG(logger, "Back to menu requested from profile editor");
    closeWidget(editor, mainMenu);
}

void ApplicationCoordinator::onSaveProfile(ProfileEditorWidget* editor, QString content) {
    LOG_DEBUG(logger, "Save profile requested");
    comController->updateProfile(content.toStdString());
    closeWidget(editor, mainMenu);
}