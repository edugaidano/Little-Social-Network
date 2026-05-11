#include "../ApplicationCoordinator.h"

void ApplicationCoordinator::onSearchBack(SearchWidget* search) {
    LOG_DEBUG(logger, "Back to main menu requested from search");
    closeWidget(search, mainMenu);
}

void ApplicationCoordinator::onSearchProfile(SearchWidget* search, QString username) {
    LOG_DEBUG(logger, "Search profile requested for user: " + username.toStdString());
    PROFILE_S* p = comController->searchProfile(username.toStdString());
    if (p == NULL) 
        return;
    
    ProfileWidget *profile = openWidget(new ProfileWidget(logger, p->username, p->content, tr("Continue Searching")));
    free(p->username);
    free(p->content);
    delete p;

    setupSearchedProfileConnections(profile, search);
}