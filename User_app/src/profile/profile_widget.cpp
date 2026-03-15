#include "profile_widget.h"
#include "ui_profile_widget.h"

ProfileWidget::ProfileWidget(const QString &username, const QString &profileContent, const QString &extraAction, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ProfileWidget)
{
    ui->setupUi(this);
    ui->usernameLabel->setText(username);
    ui->contentLabel->setText(profileContent);
    ui->actionButton->setText(extraAction);

    connect(ui->backButton, &QPushButton::clicked, this, [this]() {emit backToMenuRequested();});
    connect(ui->actionButton, &QPushButton::clicked, this, [this]() {emit actionRequested();});
}

ProfileWidget::~ProfileWidget() {
    delete ui;
}