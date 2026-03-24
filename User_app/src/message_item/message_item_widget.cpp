#include "message_item_widget.h"
#include "ui_message_item_widget.h"

MessageItemWidget::MessageItemWidget(LOG_T &logger, bool seen, const uint32_t messageId, const QString &date, const QString &sender, const QString &subject, QWidget *parent) :
    QWidget(parent),
    logger(logger),
    ui(new Ui::MessageItemWidget),
    messageId(messageId)
{
    ui->setupUi(this);
    ui->senderLabel->setText(sender);
    ui->dateLabel->setText(date);
    ui->subjectLabel->setText(subject);
    ui->seenBox->setChecked(seen);

    LOG_DEBUG(logger, "MessageItemWidget initialized with ID: " + std::to_string(messageId));
}

MessageItemWidget::~MessageItemWidget() {
    delete ui;
}

void MessageItemWidget::mousePressEvent(QMouseEvent *event) {
    emit clicked(messageId);
}

const QString MessageItemWidget::getDate() {
    return ui->dateLabel->text();
}

const QString MessageItemWidget::getSender() {
    return ui->senderLabel->text();
}

const QString MessageItemWidget::getSubject() {
    return ui->subjectLabel->text();
}