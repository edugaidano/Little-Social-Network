#include "WidgetController/InboxController.h"
#include "WidgetController/MessageController.h"

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
    PACKAGE_T* requestPkg = createPackage(MESSAGES_REQUEST);
    addItem(requestPkg, (void*)username.c_str(), username.size() + 1);
    PACKAGE_T* recvdPkg = appController.doRequestToServer(requestPkg, MESSAGES);
    freePackage(requestPkg);

    if (!recvdPkg)
        return;
        
    InboxWidget* w = (InboxWidget*)widget;
    while (recvdPkg->bufferSize != 0) {
        uint32_t* idPtr = (uint32_t*)getItem(recvdPkg);
        uint8_t* seenPtr = (uint8_t*)getItem(recvdPkg);
        char* date = (char*)getItem(recvdPkg);
        char* sender = (char*)getItem(recvdPkg);
        char* subject = (char*)getItem(recvdPkg);
        
        w->addMessageItem(*idPtr, *seenPtr, date, sender, subject);
        
        free(idPtr);
        free(seenPtr);
        free(date);
        free(sender);
        free(subject);
    }

    freePackage(recvdPkg);
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