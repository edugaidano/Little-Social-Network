#include "search_widget.h"
#include "ui_search_widget.h"

SearchWidget::SearchWidget(LOG_T &logger, QWidget *parent) :
    QWidget(parent),
    logger(logger),
    ui(new Ui::SearchWidget)
{
    ui->setupUi(this);

    connect(ui->searchButton, &QPushButton::clicked, this, &SearchWidget::onSearchButtonClicked);
    connect(ui->backButton, &QPushButton::clicked, this, &SearchWidget::onBackButtonClicked);

    LOG_DEBUG(logger, "SearchWidget initialized");
}

SearchWidget::~SearchWidget() {
    delete ui;
}

void SearchWidget::onSearchButtonClicked() {
    LOG_INFO(logger, "Search button clicked");
    QString username = ui->searchLine->text();

    //TODO: Validar existencia del usuario

    emit searchProfile(username);
}

void SearchWidget::onBackButtonClicked() {
    LOG_INFO(logger, "Back button clicked on Search Widget");
    emit backToMainMenu();
}