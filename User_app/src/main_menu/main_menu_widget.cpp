#include "main_menu_widget.h"
#include "ui_main_menu_widget.h"

MainMenuWidget::MainMenuWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::MainMenuWidget)
{
    ui->setupUi(this);

    connect(ui->viewProfileButton, &QPushButton::clicked, this, [this]() { emit viewProfileRequested(); });
    connect(ui->searchProfilebutton, &QPushButton::clicked, this, [this]() { emit searchProfileRequested(); });
    connect(ui->viewMessagesButton, &QPushButton::clicked, this, [this]() { emit viewMessagesRequested(); });
    connect(ui->sendMessageButton, &QPushButton::clicked, this, [this]() { emit sendMessageRequested(); });
    connect(ui->closeButton, &QPushButton::clicked, this, [this]() { emit logoutRequested(); });
}

MainMenuWidget::~MainMenuWidget() {
    delete ui;
}

