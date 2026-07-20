#include "Widget/main_menu_widget.h"
#include "ui_main_menu_widget.h"

MainMenuWidget::MainMenuWidget(LOG_T &logger, QWidget *parent) :
    QWidget(parent),
    logger(logger),
    ui(new Ui::MainMenuWidget)
{
    ui->setupUi(this);

    connect(ui->viewProfileButton, &QPushButton::clicked, this, &MainMenuWidget::onViewProfileButtonClicked);
    connect(ui->searchProfilebutton, &QPushButton::clicked, this, &MainMenuWidget::onSearchProfileButtonClicked);
    connect(ui->viewMessagesButton, &QPushButton::clicked, this, &MainMenuWidget::onViewMessagesButtonClicked);
    connect(ui->sendMessageButton, &QPushButton::clicked, this, &MainMenuWidget::onSendMessageButtonClicked);
    connect(ui->logOutButton, &QPushButton::clicked, this, &MainMenuWidget::onLogoutButtonClicked);

    LOG_DEBUG(logger, "MainMenuWidget initialized");
}

void MainMenuWidget::changeEvent(QEvent *event) {
    if (event->type() == QEvent::LanguageChange) {
        ui->retranslateUi(this);
    }

    QWidget::changeEvent(event);
}

MainMenuWidget::~MainMenuWidget() {
    delete ui;
}

void MainMenuWidget::onViewProfileButtonClicked() {
    LOG_INFO(logger, "View Profile button clicked");
    emit viewProfileRequested();
}

void MainMenuWidget::onSearchProfileButtonClicked() {
    LOG_INFO(logger, "Search Profile button clicked");
    emit searchProfileRequested();
}

void MainMenuWidget::onViewMessagesButtonClicked() {
    LOG_INFO(logger, "View Messages button clicked");
    emit viewMessagesRequested();
}

void MainMenuWidget::onSendMessageButtonClicked() {
    LOG_INFO(logger, "Send Message button clicked");
    emit sendMessageRequested();
}

void MainMenuWidget::onLogoutButtonClicked() {
    LOG_INFO(logger, "Logout button clicked");
    emit logoutRequested();
}
