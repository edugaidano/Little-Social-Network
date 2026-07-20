#include "WidgetController/MessageEditorController.h"

MessageEditorController::MessageEditorController(
    LOG_T& logger,
    AppController& appController,
    std::string username,
    QWidget* previousWidget
) 
    : WidgetController(logger, appController, previousWidget),
    username(username)
{
    widget = new SendMessageWidget(logger, previousWidget);
    setupConnections();
    appController.setCurrentWidget(widget);
}

MessageEditorController::~MessageEditorController() {
    LOG_DEBUG(logger, "Deleting MessageEditorController");
    appController.removeWidget(widget);
    widget->deleteLater();
}

void MessageEditorController::setupConnections() {
    connect((SendMessageWidget*)widget, &SendMessageWidget::cancelMessage, this, &MessageEditorController::onBackRequested);
    connect((SendMessageWidget*)widget, &SendMessageWidget::sendMessage, this, &MessageEditorController::onSendRequested);
}

void MessageEditorController::onBackRequested() {
    LOG_INFO(logger, "Back requested from message editor");
    appController.setCurrentWidget(previousWidget);
    this->deleteLater();
}

void MessageEditorController::onSendRequested(std::string destinatary, std::string subject, std::string content) {
    LOG_INFO(logger, "Send requested from message editor");

    std::time_t t = std::time(nullptr);
    std::tm tm{};

#ifdef _WIN32
    localtime_s(&tm, &t);
#else
    localtime_r(&t, &tm);
#endif

    std::ostringstream oss;
    oss << std::put_time(&tm, "%d - %m - %Y");

    PACKAGE_T* messagePkg = createPackage(SEND_MESSAGE);
    addItem(messagePkg, (void*)destinatary.c_str(), destinatary.size() + 1);
    addItem(messagePkg, (void*)oss.str().c_str(), oss.str().size() + 1);
    addItem(messagePkg, (void*)username.c_str(), username.size() + 1);
    addItem(messagePkg, (void*)subject.c_str(), subject.size() + 1);
    addItem(messagePkg, (void*)content.c_str(), content.size() + 1);
    PACKAGE_T* recvdPkg = appController.doRequestToServer(messagePkg, SEND_REPLY);
    freePackage(messagePkg);
    
    if (!recvdPkg)
        return;

    char* item = (char*)getItem(recvdPkg);
    freePackage(recvdPkg);
    if (item == std::string("OK")) {
        LOG_INFO(logger, "Message sended");
        DIALOG_INFO(nullptr, tr("Message sent"));
    } else {
        LOG_ERROR(logger, "SEND_REPLY item diferent to OK");
        DIALOG_ERROR(nullptr, tr("Something went wrong at sending."));
    }
    free(item);
    
    appController.setCurrentWidget(previousWidget);
    this->deleteLater();
}