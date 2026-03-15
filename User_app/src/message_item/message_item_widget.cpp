#include "message_item_widget.h"
#include "ui_message_item_widget.h"

MessageItemWidget::MessageItemWidget(const uint32_t messageId, bool seen, const QString &date, const QString &sender, const QString &subject, QWidget *parent)
    : QWidget(parent), 
    ui(new Ui::MessageItemWidget), 
    messageId(messageId)
{
    ui->setupUi(this);
    ui->senderLabel->setText(sender);
    ui->dateLabel->setText(date);
    ui->subjectLabel->setText(subject);
    ui->seenBox->setChecked(seen);
}

MessageItemWidget::~MessageItemWidget() {
    delete ui;
}

void MessageItemWidget::mousePressEvent(QMouseEvent *event) {
    emit clicked(messageId);
}