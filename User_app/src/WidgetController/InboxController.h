#ifndef INBOX_CONTROLLER_H
#define INBOX_CONTROLLER_H

#include "WidgetController.h"
#include "../widgets/messages_interface/messages_interface_widget.h"

class InboxController : public WidgetController {
private:
    std::string username;

    void setupConnections() override;

    void requestMessageItems();

    void onBackRequested();
    void onMessageSelected(uint32_t id);
public:
    InboxController(
        LOG_T& logger,
        AppController& appController,
        std::string username,
        QWidget* previousWidget
    );
    ~InboxController();

    void markMessageAsSeen(uint32_t id);
    void removeMessage(uint32_t id);
};

#endif