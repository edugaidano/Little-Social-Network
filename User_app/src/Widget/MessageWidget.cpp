#include "Widget/MessageWidget.h"
#include "ui_MessageWidget.h"

MessageWidget::MessageWidget (
    LOG_T &logger,
    uint32_t id, 
    QString date,
    QString sender,
    QString subject, 
    QString content, 
    QWidget *parent
) :
    QWidget(parent),
    logger(logger),
    ui(new Ui::MessageWidget),
    messageId(id)
{
    ui->setupUi(this);
    ui->dateLabel->setText(date);
    ui->senderLabel->setText(sender);
    ui->subjectLabel->setText(subject);
    ui->contentPlainText->setPlainText(content);

    connect(ui->backButton, &QPushButton::clicked, this, &MessageWidget::onBackButtonClicked);
    connect(ui->deleteButton, &QPushButton::clicked, this, &MessageWidget::onDeleteButtonClicked);

    LOG_DEBUG(logger, "MessageWidget initialized with ID: " + std::to_string(messageId));
}

MessageWidget::~MessageWidget() {
    delete ui;
}

void MessageWidget::onBackButtonClicked() {
    LOG_INFO(logger, "Back button clicked on message " + std::to_string(messageId));
    emit backButtonClicked();
}

void MessageWidget::onDeleteButtonClicked() {
    LOG_INFO(logger, "Delete button clicked on message " + std::to_string(messageId));
    emit deleteButtonClicked(messageId);
}