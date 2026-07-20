#include "Widget/InboxWidget.h"
#include "ui_InboxWidget.h"

InboxWidget::InboxWidget(LOG_T &logger, QWidget *parent) :
    QWidget(parent),
    logger(logger),
    ui(new Ui::InboxWidget)
{
    ui->setupUi(this);

    connect(ui->backButton, &QPushButton::clicked, this, &InboxWidget::onBackButtonClicked);

    LOG_DEBUG(logger, "InboxWidget initialized");
}

InboxWidget::~InboxWidget() {
    delete ui;
}

void InboxWidget::onBackButtonClicked() {
    LOG_INFO(logger, "Back to main menu button clicked");
    emit backToMainMenu();
}

void InboxWidget::onMessageItemClicked(const uint32_t messageId) {
    LOG_INFO(logger, "Message item clicked with ID: " + std::to_string(messageId));
    emit messageSelected(messageId);
}

void InboxWidget::addMessageItem(const uint32_t messageId, bool seen, const QString &date, const QString &sender, const QString &subject) {
    MessageItemWidget *item = new MessageItemWidget(logger, seen, messageId, date, sender, subject);
    ui->messageAreaLayout->addWidget(item);
    ui->messageArea->adjustSize();
    messageMap[messageId] = item;
    
    connect(item, &MessageItemWidget::clicked, this, &InboxWidget::onMessageItemClicked);
}

MessageItemWidget* InboxWidget::findMessageById(uint32_t id) {
    auto it = messageMap.find(id);
    if (it != messageMap.end()) {
        return it->second;
    }
    return nullptr;
}

void InboxWidget::removeMessage(uint32_t id) {
    auto it = messageMap.find(id);
    if (it != messageMap.end()) {
        MessageItemWidget *item = it->second;

        ui->messageAreaLayout->removeWidget(item);
        messageMap.erase(it);

        delete item;

        checkMessagesToDisplay();
    }
}

void InboxWidget::checkMessagesToDisplay() {
    if (messageMap.empty()) {
        LOG_INFO(logger, "No messages to display");
        DIALOG_INFO(this, QObject::tr("You do not have messages"));
        emit backToMainMenu();
    }
}