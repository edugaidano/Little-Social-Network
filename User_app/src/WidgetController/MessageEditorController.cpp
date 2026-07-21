#include "WidgetController/MessageEditorController.h"
#include "Protocol/send_message.h"
#include "ProtocolResult/ProtocolNetworkResult.h"

MessageEditorController::MessageEditorController(
    LOG_T& logger,
    AppController& appController,
    std::string username,
    QWidget* previousWidget
) 
    : WidgetController(logger, appController, previousWidget),
    username(username)
{
    widget = new MessageEditorWidget(logger, previousWidget);
    setupConnections();
    appController.setCurrentWidget(widget);
}

MessageEditorController::~MessageEditorController() {
    LOG_DEBUG(logger, "Deleting MessageEditorController");
    appController.removeWidget(widget);
    widget->deleteLater();
}

void MessageEditorController::setupConnections() {
    connect((MessageEditorWidget*)widget, &MessageEditorWidget::backRequested, this, &MessageEditorController::onBackRequested);
    connect((MessageEditorWidget*)widget, &MessageEditorWidget::sendMessage, this, &MessageEditorController::onSendRequested);
}

void MessageEditorController::onBackRequested() {
    LOG_INFO(logger, "Back requested from message editor");
    appController.setCurrentWidget(previousWidget);
    this->deleteLater();
}

void MessageEditorController::onSendRequested(std::string destinatary, std::string subject, std::string content) {
    LOG_INFO(logger, "Send requested from message editor");
    std::unique_ptr<ProtocolResult> result = sendMessageProtocol(logger, appController.getCommunicator(), username, destinatary, subject, content);
    if (auto* networkResult = dynamic_cast<ProtocolNetworkResult*>(result.get())) {
        this->ShowError(networkResult->getError());
        return;
    }
    switch (result->getCode()) {
        case ResultCode::OK :
            DIALOG_INFO(widget, tr("Message sent"));
            appController.setCurrentWidget(previousWidget);
            this->deleteLater();
            break;
        default:
            DIALOG_ERROR(widget, tr("Something went wrong."));
            break;
    }    
}