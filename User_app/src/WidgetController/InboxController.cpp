#include "WidgetController/InboxController.h"
#include "WidgetController/MessageController.h"
#include "Protocol/request_inbox.h"
#include "ProtocolResult/ProtocolNetworkResult.h"
#include "ProtocolResult/ProtocolInboxResult.h"

InboxController::InboxController(
    LOG_T& logger,
    AppController& appController,
    std::string username,
    QWidget* previousWidget
) 
    : WidgetController(logger, appController, previousWidget),
    username(username)
{
    widget = new InboxWidget(logger, previousWidget);
    requestMessageItems();
    setupConnections();
    appController.setCurrentWidget(widget);
    InboxWidget* w = (InboxWidget*)widget;
    w->checkMessagesToDisplay();
}

InboxController::~InboxController() {
    LOG_DEBUG(logger, "Deleting InboxController.");
    appController.removeWidget(widget);
    widget->deleteLater();
}

void InboxController::setupConnections() {
    connect((InboxWidget*)widget, &InboxWidget::backToMainMenu, this, &InboxController::onBackRequested);
    connect((InboxWidget*)widget, &InboxWidget::messageSelected, this, &InboxController::onMessageSelected);
}

void InboxController::requestMessageItems() {
    std::unique_ptr<ProtocolResult> result = requestInboxProtocol(logger, appController.getCommunicator(), username);
    if (auto* networkResult = dynamic_cast<ProtocolNetworkResult*>(result.get())) {
        this->ShowError(networkResult->getError());
        return;
    }
    if (auto* inboxResult = dynamic_cast<ProtocolInboxResult*>(result.get())) {
        auto items = inboxResult->getItems();
        InboxWidget* w = (InboxWidget*)widget;
        for (auto item : items) {
            w->addMessageItem(item.id, item.seen, item.date.c_str(), item.sender.c_str(), item.subject.c_str());
        }
    } else {
        DIALOG_ERROR(widget, tr("Something went wrong."));
    }
}

void InboxController::onBackRequested() {
    LOG_INFO(logger, "Back requested from inbox");
    this->deleteLater();
}

void InboxController::onMessageSelected(uint32_t id) {
    LOG_INFO(logger, "Message selected");
    InboxWidget* w = (InboxWidget*)widget;
    MessageItemWidget* item = w->findMessageById(id);
    
    new MessageController(
        logger,
        appController,
        *this,
        username,
        id,
        item->getDate(),
        item->getSender(),
        item->getSubject(),
        widget
    );
}

void InboxController::markMessageAsSeen(uint32_t id) {
    InboxWidget* w = (InboxWidget*)widget;
    MessageItemWidget* item = w->findMessageById(id);
    item->markAsSeen();
}

void InboxController::removeMessage(uint32_t id) {
    InboxWidget* w = (InboxWidget*)widget;
    w->removeMessage(id);
}