#include "Widget/ProfileEditorWidget.h"
#include "ui_ProfileEditorWidget.h"

ProfileEditorWidget::ProfileEditorWidget(LOG_T &logger, const QString &username, const QString &profileContent, QWidget *parent) :
    QWidget(parent),
    logger(logger),
    ui(new Ui::ProfileEditorWidget)
{
    ui->setupUi(this);
    ui->usernameLabel_1->setText(username);
    ui->usernameLabel_2->setText(username);
    ui->profileContentPlain->setPlainText(profileContent);

    connect(ui->saveButton, &QPushButton::clicked, this, &ProfileEditorWidget::onSaveButtonClicked);
    connect(ui->cancelButton, &QPushButton::clicked, this, &ProfileEditorWidget::onBackButtonClicked);

    LOG_DEBUG(logger, "ProfileEditorWidget initialized for user");
}

ProfileEditorWidget::~ProfileEditorWidget() {
    delete ui;
}

void ProfileEditorWidget::onSaveButtonClicked() {
    LOG_INFO(logger, "Save button clicked on the Profile Editor");
    QString profileContent = ui->profileContentTextEdit->toPlainText();
    emit saveProfileRequested(profileContent);
}

void ProfileEditorWidget::onBackButtonClicked() {
    LOG_INFO(logger, "Back button clicked on the Profile Editor");
    emit backToMenuRequested();
}