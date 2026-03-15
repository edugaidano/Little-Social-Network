#include "send_message_widget.h"
#include "ui_send_message_widget.h"

SendMessageWidget::SendMessageWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::SendMessageWidget)
{
    ui->setupUi(this);

    connect(ui->sendButton, &QPushButton::clicked, this, [this]() {
        emit sendMessage(ui->destinataryLineEdit->text(), ui->subjectLineEdit->text(), ui->messageTextEdit->toPlainText());
    });

    connect(ui->cancelButton, &QPushButton::clicked, this, [this]() { emit cancelMessage();});
}

SendMessageWidget::~SendMessageWidget() {
    delete ui;
}