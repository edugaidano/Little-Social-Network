#include "send_message_widget.h"
#include "ui_send_message_widget.h"

SendMessageWidget::SendMessageWidget(LOG_T &logger, QWidget *parent) :
    QWidget(parent),
    logger(logger),
    ui(new Ui::SendMessageWidget)
{
    ui->setupUi(this);

    connect(ui->sendButton, &QPushButton::clicked, this, &SendMessageWidget::onSendButtonClicked);
    connect(ui->cancelButton, &QPushButton::clicked, this, &SendMessageWidget::onCancelButtonClicked);

    LOG_DEBUG(logger, "SendMessageWidget initialized");
}

SendMessageWidget::~SendMessageWidget() {
    delete ui;
}

void SendMessageWidget::onSendButtonClicked() {
    LOG_INFO(logger, "Send button clicked");
    emit sendMessage(ui->destinataryLineEdit->text(), ui->subjectLineEdit->text(), ui->messageTextEdit->toPlainText());
}

void SendMessageWidget::onCancelButtonClicked() {
    LOG_INFO(logger, "Cancel button clicked on Send Message Widget");
    emit cancelMessage();
}