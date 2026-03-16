#include "profile_widget.h"
#include "ui_profile_widget.h"

ProfileWidget::ProfileWidget(LOG_T &logger, const QString &username, const QString &profileContent, const QString &extraAction, QWidget *parent) :
    QWidget(parent),
    logger(logger),
    username(username),
    profileContent(profileContent),
    extraAction(extraAction),
    ui(new Ui::ProfileWidget)
{
    ui->setupUi(this);
    ui->usernameLabel->setText(username);
    ui->contentLabel->setText(profileContent);
    ui->actionButton->setText(extraAction);

    connect(ui->backButton, &QPushButton::clicked, this, &ProfileWidget::onBackButtonClicked);
    connect(ui->actionButton, &QPushButton::clicked, this, &ProfileWidget::onActionButtonClicked);

    LOG_DEBUG(logger, "ProfileWidget initialized for user: " + username.toStdString() + " with action: " + extraAction.toStdString());
}

ProfileWidget::~ProfileWidget() {
    delete ui;
}

void ProfileWidget::onBackButtonClicked() {
    LOG_INFO(logger, "Back button clicked on a profile");
    emit backToMenuRequested();
}   

void ProfileWidget::onActionButtonClicked() {
    LOG_INFO(logger, "Action button clicked on a profile");
    emit actionRequested();
}