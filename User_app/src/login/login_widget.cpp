#include "login_widget.h"
#include "ui_login_widget.h"

LoginWidget::LoginWidget(LOG_T &logger, QWidget *parent) :
    QWidget(parent),
    logger(logger),
    ui(new Ui::LoginWidget)
{
    ui->setupUi(this);

    connect(ui->loginButton, &QPushButton::clicked, this, &LoginWidget::onLoginButtonClicked);
    connect(ui->registerButton, &QPushButton::clicked, this, &LoginWidget::onRegisterButtonClicked);

    LOG_DEBUG(logger, "LoginWidget initialized");
}

LoginWidget::~LoginWidget() {
    delete ui;
}

void LoginWidget::onLoginButtonClicked() {
    LOG_INFO(logger, "Login button clicked");
    QString user = ui->lineEdit->text();

    //TODO: Validar usuario

    emit loginRequested(user);
}

void LoginWidget::onRegisterButtonClicked() {
    LOG_INFO(logger, "Register button clicked");
    QString user = ui->lineEdit->text();

    //TODO: Validar usuario

    emit registerRequested(user);
}