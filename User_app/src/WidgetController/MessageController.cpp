#include "WidgetController/MessageController.h"
#include "Protocol/delete_message.h"
#include "Protocol/request_message.h"
#include "ProtocolResult/ProtocolNetworkResult.h"
#include "ProtocolResult/ProtocolContentResult.h"

MessageController::MessageController( 
    LOG_T& logger, 
    AppController& appController,
    InboxController& inboxController,
    std::string username,
    uint32_t id, 
    std::string date,
    std::string sender,
    std::string subject,
    QWidget* previousWidget
) 
    : WidgetController(logger, appController, previousWidget),
    inboxController(inboxController),
    id(id),
    username(username)
{
    auto content = requestContent();
    if (!content.has_value()){
        this->deleteLater();
        return;
    }

    widget = new MessageWidget(logger, id, date.c_str(), sender.c_str(), subject.c_str(), content.value().c_str(), previousWidget);
    setupConnections();
    appController.setCurrentWidget(widget);
}

MessageController::~MessageController() {
    LOG_DEBUG(logger, "Deleting MessageController");
    if (widget) {   
        appController.removeWidget(widget);
        widget->deleteLater();
    }
}

void MessageController::setupConnections() {
    connect((MessageWidget*)widget, &MessageWidget::backButtonClicked, this, &MessageController::onBackRequested);
    connect((MessageWidget*)widget, &MessageWidget::deleteButtonClicked, this, &MessageController::onDeleteRequested);
}

std::optional<std::string> MessageController::requestContent() {
    std::unique_ptr<ProtocolResult> result = requestMessageProtocol(logger, appController.getCommunicator(), username, id);
    if (auto* networkResult = dynamic_cast<ProtocolNetworkResult*>(result.get())) {
        this->ShowError(networkResult->getError());
        return std::nullopt;
    }
    if (auto* contentResult = dynamic_cast<ProtocolContentResult*>(result.get())) {
        return contentResult->getContent();;
    } 

    DIALOG_ERROR(widget, tr("Something went wrong."));
    return std::nullopt;
}

void MessageController::onBackRequested() {
    LOG_INFO(logger, "Back requested from a message");
    inboxController.markMessageAsSeen(id);
    appController.setCurrentWidget(previousWidget);
    this->deleteLater();
}

void MessageController::onDeleteRequested() {
    std::unique_ptr<ProtocolResult> result = deleteMessageProtocol(logger, appController.getCommunicator(), username, id);
    if (auto* networkResult = dynamic_cast<ProtocolNetworkResult*>(result.get())) {
        this->ShowError(networkResult->getError());
        return;
    }
    switch (result->getCode()) {
        case ResultCode::OK :
            DIALOG_INFO(widget, tr("Message deleted."));
            inboxController.removeMessage(id);
            appController.setCurrentWidget(previousWidget);
            this->deleteLater();
            break;
        default:
            DIALOG_ERROR(widget, tr("Something went wrong."));
            break;
    }
}