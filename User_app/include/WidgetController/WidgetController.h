#ifndef WIDGET_CONTROLLER_H
#define WIDGET_CONTROLLER_H

#include <QWidget>

#include "AppController.h"
#include "NetworkException/NetworkError.h"
#include "dialog.h"

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

    virtual void ShowError(const NetworkError & e) {
        QString message;
        switch (e) {
            case NetworkError::SendError:
                message = tr("Something went wrong while sending the request.");
                break;
            case NetworkError::ConnectionError:
                message = tr("Error making connection with the server.\n Check if the configuration is correct.");
                break;
            case NetworkError::ReceiveError:
                message = tr("Something went wrong while receiving the reply.");
                break;

            case NetworkError::UnexpectedPackage:
                message = tr("The package received is different from what was expected.");
                break;
        }
        DIALOG_ERROR(widget, message);
    }

    LOG_T& logger;
    QWidget* widget = nullptr;
    AppController& appController;
    QWidget* previousWidget;
};


#endif