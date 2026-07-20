#include "Widget/MessageEditorWidget.h"
#include "ui_MessageEditorWidget.h"

MessageEditorWidget::MessageEditorWidget(LOG_T &logger, QWidget *parent) :
    QWidget(parent),
    logger(logger),
    ui(new Ui::MessageEditorWidget)
{
    ui->setupUi(this);

    connect(ui->sendButton, &QPushButton::clicked, this, &MessageEditorWidget::onSendButtonClicked);
    connect(ui->backButton, &QPushButton::clicked, this, &MessageEditorWidget::onBackButtonClicked);

    LOG_DEBUG(logger, "MessageEditorWidget initialized");
}

MessageEditorWidget::~MessageEditorWidget() {
    delete ui;
}

void MessageEditorWidget::onSendButtonClicked() {
    LOG_INFO(logger, "Send button clicked");
    if (ui->destinataryLineEdit->text().isEmpty()){
        LOG_WARNING(logger, "Destinatary is empty");
        DIALOG_WARNING(this, QObject::tr("Destinatary is empty"));
        return;
    }
    emit sendMessage(ui->destinataryLineEdit->text().toStdString(), ui->subjectLineEdit->text().toStdString(), ui->messageTextEdit->toPlainText().toStdString());
}

void MessageEditorWidget::onBackButtonClicked() {
    LOG_INFO(logger, "Back button clicked on Send Message Widget");
    emit backRequested();
}