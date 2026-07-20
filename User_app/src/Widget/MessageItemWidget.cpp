#include "Widget/MessageItemWidget.h"
#include "ui_MessageItemWidget.h"

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

std::string MessageItemWidget::getDate() {
    return ui->dateLabel->text().toStdString();
}

std::string MessageItemWidget::getSender() {
    return ui->senderLabel->text().toStdString();
}

std::string MessageItemWidget::getSubject() {
    return ui->subjectLabel->text().toStdString();
}

void MessageItemWidget::markAsSeen() {
    ui->seenBox->setChecked(true);
}