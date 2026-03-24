#include "messages_interface_widget.h"
#include "ui_messages_interface_widget.h"

MessagesInterfaceWidget::MessagesInterfaceWidget(LOG_T &logger, QWidget *parent) :
    QWidget(parent),
    logger(logger),
    ui(new Ui::MessagesInterfaceWidget)
{
    ui->setupUi(this);

    connect(ui->backButton, &QPushButton::clicked, this, &MessagesInterfaceWidget::onBackButtonClicked);

    LOG_DEBUG(logger, "MessagesInterfaceWidget initialized");
}

MessagesInterfaceWidget::~MessagesInterfaceWidget() {
    delete ui;
}

void MessagesInterfaceWidget::onBackButtonClicked() {
    LOG_INFO(logger, "Back to main menu button clicked");
    emit backToMainMenu();
}

void MessagesInterfaceWidget::onMessageItemClicked(const uint32_t messageId) {
    LOG_INFO(logger, "Message item clicked with ID: " + std::to_string(messageId));
    emit messageSelected(messageId);
}

void MessagesInterfaceWidget::addMessageItem(const uint32_t messageId, bool seen, const QString &date, const QString &sender, const QString &subject) {
    MessageItemWidget *item = new MessageItemWidget(logger, seen, messageId, date, sender, subject);
    ui->messageAreaLayout->addWidget(item);
    messageMap[messageId] = item;
    
    connect(item, &MessageItemWidget::clicked, this, &MessagesInterfaceWidget::onMessageItemClicked);
}

MessageItemWidget* MessagesInterfaceWidget::findMessageById(uint32_t id) {
    auto it = messageMap.find(id);
    if (it != messageMap.end()) {
        return it->second;
    }
    return nullptr;
}
