#include "search_widget.h"
#include "ui_search_widget.h"

SearchWidget::SearchWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::SearchWidget)
{
    ui->setupUi(this);

    connect(ui->searchButton, &QPushButton::clicked, this, &SearchWidget::on_searchButton_clicked);
    connect(ui->backButton, &QPushButton::clicked, this, [this]() { emit backToMainMenu();});
}

SearchWidget::~SearchWidget() {
    delete ui;
}

void SearchWidget::on_searchButton_clicked() {
    QString username = ui->searchLine->text();

    //TODO: Validar existencia del usuario

    emit searchProfile(username);
}