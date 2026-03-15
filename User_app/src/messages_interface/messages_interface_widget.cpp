#include "messages_interface_widget.h"
#include "ui_messages_interface_widget.h"
#include "../message_item/message_item_widget.h"

MessagesInterfaceWidget::MessagesInterfaceWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::MessagesInterfaceWidget)
{
    ui->setupUi(this);

    connect(ui->backButton, &QPushButton::clicked, this, &MessagesInterfaceWidget::backToMainMenu);
}

MessagesInterfaceWidget::~MessagesInterfaceWidget() {
    delete ui;
}

void MessagesInterfaceWidget::addMessageItem(const uint32_t messageId, bool seen, const QString &date, const QString &sender, const QString &subject) {
    MessageItemWidget *item = new MessageItemWidget(messageId, seen, date, sender, subject);
    ui->messageAreaLayout->addWidget(item);
    connect(item, &MessageItemWidget::clicked, this, [this](const uint32_t messageId) { emit messageSelected(messageId); });
}