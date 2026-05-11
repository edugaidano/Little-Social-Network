#include "ApplicationCoordinator.h"
#include <QVBoxLayout>

ApplicationCoordinator::ApplicationCoordinator(LOG_T &logger, CONFIG_D &config, QApplication &app, QWidget *parent) :
    QWidget(parent), 
    logger(logger),
    config(config),
    app(app)
{
    stack = new QStackedWidget();

    login = new LoginWidget(logger);
    mainMenu = new MainMenuWidget(logger);

    stack->addWidget(login);
    stack->addWidget(mainMenu);

    QVBoxLayout *layout = new QVBoxLayout(this);
    layout->addWidget(stack);

    setupLoginConnections();
    setupMainMenuConnections();

    setLanguage();

    LOG_DEBUG(logger, "ApplicationCoordinator initialized");
}

