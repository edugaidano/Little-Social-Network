#include "ApplicationCoordinator.h"

// On header: T* ApplicationCoordinator::openWidget(T* widget);

void ApplicationCoordinator::closeWidget(QWidget* current, QWidget* backTo) {
    stack->setCurrentWidget(backTo);
    destroyWidget(current);
}

void ApplicationCoordinator::destroyWidget(QWidget* widget) {
    stack->removeWidget(widget);
    widget->deleteLater();
}

void ApplicationCoordinator::setLanguage() {
    app.removeTranslator(&translator);

    if (translator.load(("app_" + config["LANGUAGE"]).c_str())) {
        app.installTranslator(&translator);
    }
}