#ifndef MESSAGE_EDITOR_CONTROLLER_H
#define MESSAGE_EDITOR_CONTROLLER_H

#include "WidgetController.h"
#include "Widget/send_message_widget.h"

class MessageEditorController : public WidgetController {
private:
    std::string username;

    void setupConnections() override;

    void onBackRequested();
    void onSendRequested(std::string destinatary, std::string subject, std::string content);
public:
    MessageEditorController(
        LOG_T& logger,
        AppController& appController,
        std::string username,
        QWidget* previousWidget
    );
    ~MessageEditorController();
};


#endif