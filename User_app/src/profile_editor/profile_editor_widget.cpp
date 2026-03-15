#include "profile_editor_widget.h"
#include "ui_profile_editor_widget.h"

ProfileEditorWidget::ProfileEditorWidget(const QString &username, const QString &profileContent, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ProfileEditorWidget)
{
    ui->setupUi(this);
    ui->usernameLabel_1->setText(username);
    ui->usernameLabel_2->setText(username);
    ui->profileContentLabel->setText(profileContent);

    connect(ui->saveButton, &QPushButton::clicked, this, &ProfileEditorWidget::onSaveButtonClicked);
    connect(ui->cancelButton, &QPushButton::clicked, this, [this]() {emit backToMenuRequested();});
}

ProfileEditorWidget::~ProfileEditorWidget() {
    delete ui;
}

void ProfileEditorWidget::onSaveButtonClicked() {
    QString profileContent = ui->profileContentTextEdit->toPlainText();
    emit saveProfileRequested(profileContent);
}


