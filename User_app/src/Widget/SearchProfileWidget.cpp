#include "Widget/SearchProfileWidget.h"
#include "ui_SearchProfileWidget.h"

SearchProfileWidget::SearchProfileWidget(LOG_T &logger, QWidget *parent) :
    QWidget(parent),
    logger(logger),
    ui(new Ui::SearchProfileWidget)
{
    ui->setupUi(this);

    connect(ui->searchButton, &QPushButton::clicked, this, &SearchProfileWidget::onSearchButtonClicked);
    connect(ui->backButton, &QPushButton::clicked, this, &SearchProfileWidget::onBackButtonClicked);

    LOG_DEBUG(logger, "SearchProfileWidget initialized");
}

SearchProfileWidget::~SearchProfileWidget() {
    delete ui;
}

void SearchProfileWidget::onSearchButtonClicked() {
    LOG_INFO(logger, "Search button clicked");
    QString username = ui->searchLine->text();

    if (username.isEmpty()) {
        LOG_WARNING(logger, "User is empty");
        DIALOG_WARNING(this, QObject::tr("User is empty"));
        return;
    }

    emit searchProfile(username);
}

void SearchProfileWidget::onBackButtonClicked() {
    LOG_INFO(logger, "Back button clicked on Search Widget");
    emit backToMainMenu();
}