#include "config_widget.h"
#include "ui_config_widget.h"

ConfigWidget::ConfigWidget(LOG_T &logger, CONFIG_D &config, QWidget *parent) : 
    QWidget(parent), 
    logger(logger), 
    ui(new Ui::ConfigWidget)
{
    ui->setupUi(this);
    ui->ipLineEdit->setPlaceholderText(config["SERVER_IP"].c_str());
    ui->portLineEdit->setPlaceholderText(config["SERVER_PORT"].c_str());
    ui->logLevelLineEdit->setPlaceholderText(config["LOG_LEVEL"].c_str());
    ui->languageLineEdit->setPlaceholderText(config["LANGUAGE"].c_str());
    
    connect(ui->saveButton, &QPushButton::clicked, this, &ConfigWidget::onSaveButtonClicked);
    connect(ui->cancelButton, &QPushButton::clicked, this, &ConfigWidget::onCancelButtonClicked);
}

ConfigWidget::~ConfigWidget() {
    delete ui;
}

void ConfigWidget::onCancelButtonClicked() {
    LOG_INFO(logger, "Cancel button clicked");
    emit backRequested();
}

void ConfigWidget::onSaveButtonClicked() {
    LOG_INFO(logger, "Save button clicked");

    CONFIG_D newConf;

    if (!ui->ipLineEdit->text().isEmpty()) {
        newConf["SERVER_IP"] = ui->ipLineEdit->text().toStdString();
    }

    if (!ui->portLineEdit->text().isEmpty()) {
        newConf["SERVER_PORT"] = ui->portLineEdit->text().toStdString();
    }

    if (!ui->logLevelLineEdit->text().isEmpty()) {
        newConf["LOG_LEVEL"] = ui->logLevelLineEdit->text().toStdString();
    }

    if (!ui->languageLineEdit->text().isEmpty()) {
        newConf["LANGUAGE"] = ui->languageLineEdit->text().toStdString();
    }

    if (newConf.empty()) {
        LOG_INFO(logger, "No changes made to configuration");
        emit backRequested();
    } else {   
        LOG_INFO(logger, "Configuration changes requested");
        emit saveRequested(newConf);
    }
}