#include "dialog.h"
#include "ui_dialog.h"

Dialog::Dialog(const QString& title, const QString& info, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog)
{
    ui->setupUi(this);
    ui->titleLabel->setText(title);
    ui->InfoLabel->setText(info);

    setFixedSize(size());
}

Dialog::~Dialog() {
    delete ui;
}