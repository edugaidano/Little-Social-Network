#ifndef MESSAGE_CONTROLLER_H
#define MESSAGE_CONTROLLER_H

#include "WidgetController.h"
#include "InboxController.h"
#include "Widget/MessageWidget.h"

class MessageController : public WidgetController {
private:
    std::string username;
    uint32_t id;
    InboxController& inboxController;

    void setupConnections() override;

    std::optional<std::string> requestContent();

    void onBackRequested();
    void onDeleteRequested();
public:
    MessageController(
        LOG_T& logger,
        AppController& appController,
        InboxController& indexController,
        std::string username,
        uint32_t id, 
        std::string date,
        std::string sender,
        std::string subject,
        QWidget* previousWidget
    );
    ~MessageController();
};

#endif