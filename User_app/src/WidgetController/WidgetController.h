#ifndef WIDGET_CONTROLLER_H
#define WIDGET_CONTROLLER_H

#include <QWidget>

#include "../AppController/AppController.h"

#include "logs/logs.h"

class WidgetController : public QObject {
    Q_OBJECT
public:
    WidgetController(
        LOG_T& logger,
        AppController& appController,
        QWidget* previousWidget = nullptr
    ) : 
        logger(logger),
        previousWidget(previousWidget),
        appController(appController)
    {}

    virtual ~WidgetController() = default;

protected:
    virtual void setupConnections() = 0;

    LOG_T& logger;
    QWidget* widget;
    AppController& appController;
    QWidget* previousWidget;
};


#endif