#include "WidgetController/MessageController.h"

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
    if (!content.has_value())
        return;

    widget = new MessageWidget(logger, id, date.c_str(), sender.c_str(), subject.c_str(), content.value().c_str(), previousWidget);
    setupConnections();
    appController.setCurrentWidget(widget);
}

MessageController::~MessageController() {
    LOG_DEBUG(logger, "Deleting MessageController");
    appController.removeWidget(widget);
    widget->deleteLater();
}

void MessageController::setupConnections() {
    connect((MessageWidget*)widget, &MessageWidget::backButtonClicked, this, &MessageController::onBackRequested);
    connect((MessageWidget*)widget, &MessageWidget::deleteButtonClicked, this, &MessageController::onDeleteRequested);
}

std::optional<std::string> MessageController::requestContent() {
    PACKAGE_T* requestPkg = createPackage(MESSAGE_REQUEST);
    addItem(requestPkg, (void*)username.c_str(), username.size() + 1);
    addItem(requestPkg, &id, sizeof(uint32_t));
    PACKAGE_T* recvdPkg = appController.doRequestToServer(requestPkg, MESSAGE);
    freePackage(requestPkg);
    if (recvdPkg == NULL)
        return std::nullopt;

    char* item = (char*)getItem(recvdPkg);
    freePackage(recvdPkg);

    if (!item) {
        LOG_ERROR(logger, "No message content received");
        DIALOG_ERROR(previousWidget, "Something went wrong while receiving the message reply.");
        return std::nullopt;
    } else {
        std::string content(item);
        free(item);
        return content;
    }
}

void MessageController::onBackRequested() {
    LOG_INFO(logger, "Back requested from a message");
    inboxController.markMessageAsSeen(id);
    appController.setCurrentWidget(previousWidget);
    this->deleteLater();
}

void MessageController::onDeleteRequested() {
    PACKAGE_T* requestPkg = createPackage(DELETE_MESSAGE_REQUEST);
    addItem(requestPkg, (void*)username.c_str(), username.size() + 1);
    addItem(requestPkg, &id, sizeof(uint32_t));
    PACKAGE_T* recvdPkg = appController.doRequestToServer(requestPkg, DELETE_MESSAGE_REPLY);
    freePackage(requestPkg);

    if (recvdPkg == NULL)
        return;

    char* item = (char*)getItem(recvdPkg);
    freePackage(recvdPkg);
    if (item == std::string("OK")) {
        LOG_INFO(logger, "Message deleted");
        DIALOG_INFO(nullptr, tr("Message deleted."));
        inboxController.removeMessage(id);
        appController.setCurrentWidget(previousWidget);
        this->deleteLater();
    } else {
        LOG_ERROR(logger, "DELETE_MESSAGE_REPLY item diferent to OK");
        DIALOG_ERROR(nullptr, tr("Something went wrong at deleting."));
    }
    free(item);
}