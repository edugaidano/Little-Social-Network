#include "login_widget.h"
#include "ui_login_widget.h"

LoginWidget::LoginWidget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::LoginWidget)
{
    ui->setupUi(this);

    connect(ui->loginButton, &QPushButton::clicked, this, &LoginWidget::onLoginButtonClicked);
    connect(ui->registerButton, &QPushButton::clicked, this, &LoginWidget::onRegisterButtonClicked);
}

LoginWidget::~LoginWidget() {
    delete ui;
}

void LoginWidget::onLoginButtonClicked() {
    QString user = ui->lineEdit->text();

    //TODO: Validar usuario

    emit loginRequested(user);
}

void LoginWidget::onRegisterButtonClicked() {
    QString user = ui->lineEdit->text();

    //TODO: Validar usuario

    emit registerRequested(user);
}