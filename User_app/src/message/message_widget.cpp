#include "message_widget.h"
#include "ui_message_widget.h"

MessageWidget::MessageWidget(const uint32_t id, const QString &date, const QString &sender, const QString &subject, const QString &content, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::MessageWidget),
    messageId(id)
{
    ui->setupUi(this);
    ui->dateLabel->setText(date);
    ui->senderLabel->setText(sender);
    ui->subjectLabel->setText(subject);
    ui->contentLabel->setText(content);

    connect(ui->backButton, &QPushButton::clicked, this, [this]() { emit backButtonClicked(); });
    connect(ui->deleteButton, &QPushButton::clicked, this, [this]() { emit deleteButtonClicked(messageId); });
}

MessageWidget::~MessageWidget() {
    delete ui;
}
