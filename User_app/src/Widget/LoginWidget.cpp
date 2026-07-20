#include "Widget/LoginWidget.h"
#include "ui_LoginWidget.h"

LoginWidget::LoginWidget(LOG_T &logger, QWidget *parent) :
    QWidget(parent),
    logger(logger),
    ui(new Ui::LoginWidget)
{
    ui->setupUi(this);

    connect(ui->mainButton, &QPushButton::clicked, this, &LoginWidget::onMainButtonClicked);
    connect(ui->secondaryButton, &QPushButton::clicked, this, &LoginWidget::onSecondaryButtonClicked);
    connect(ui->configButton, &QPushButton::clicked, this, &LoginWidget::onConfigButtonClicked);

    LOG_DEBUG(logger, "LoginWidget initialized");
}

void LoginWidget::changeEvent(QEvent *event) {
    if (event->type() == QEvent::LanguageChange) {
        ui->retranslateUi(this);

        if (isLoginMode) {
            ui->titleLabel->setText(tr("Access your account"));
            ui->mainButton->setText(tr("Login"));
            ui->secondaryLabel->setText(tr("Don't have an account?"));
            ui->secondaryButton->setText(tr("Register"));
        } else {
            ui->titleLabel->setText(tr("Create a new account"));
            ui->mainButton->setText(tr("Register"));
            ui->secondaryLabel->setText(tr("Already have an account?"));
            ui->secondaryButton->setText(tr("Login"));
        }
    }
    QWidget::changeEvent(event);
}

LoginWidget::~LoginWidget() {
    delete ui;
}

void LoginWidget::onMainButtonClicked() {
    QString user = ui->lineEdit->text();
    if (user.isEmpty()) {
        LOG_WARNING(logger, "User is empty");
        DIALOG_WARNING(this, tr("User is empty"));
        return;
    }
      
    if (isLoginMode) {
        LOG_INFO(logger, "Login button clicked");
        emit loginRequested(user);
    } else {
        LOG_INFO(logger, "Register button clicked");
        emit registerRequested(user);
    }
}

void LoginWidget::onSecondaryButtonClicked() {
    if(isLoginMode) {
        LOG_INFO(logger, "Switching to register mode");
        ui->titleLabel->setText(tr("Create a new account"));
        ui->mainButton->setText(tr("Register"));
        ui->secondaryLabel->setText(tr("Already have an account?"));
        ui->secondaryButton->setText(tr("Login"));
        isLoginMode = false;
    } else {
        LOG_INFO(logger, "Switching to login mode");
        ui->titleLabel->setText(tr("Access your account"));
        ui->mainButton->setText(tr("Login"));
        ui->secondaryLabel->setText(tr("Don't have an account?"));
        ui->secondaryButton->setText(tr("Register"));
        isLoginMode = true;
    }
}

void LoginWidget::onConfigButtonClicked() {
    LOG_INFO(logger, "Config button clicked");
    emit configRequested();
}