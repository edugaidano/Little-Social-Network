#include "config_widget.h"
#include "ui_config_widget.h"

ConfigWidget::ConfigWidget(LOG_T &logger, CONFIG_D &config, QWidget *parent) : 
    QWidget(parent), 
    logger(logger), 
    config(config), 
    ui(new Ui::ConfigWidget)
{
    ui->setupUi(this);
    ui->ipLineEdit->setPlaceholderText(config["SERVER_IP"].c_str());
    ui->portLineEdit->setPlaceholderText(config["SERVER_PORT"].c_str());
    ui->logLevelLineEdit->setPlaceholderText(config["LOG_LEVEL"].c_str());
    
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
    bool edited = false;
    if (!ui->ipLineEdit->text().isEmpty()) {   
        config["SERVER_IP"] = ui->ipLineEdit->text().toStdString();
        edited = true;
    }
    if (!ui->portLineEdit->text().isEmpty()) {   
        config["SERVER_PORT"] = ui->portLineEdit->text().toStdString();
        edited = true;
    }
    if (!ui->logLevelLineEdit->text().isEmpty()) {   
        config["LOG_LEVEL"] = ui->logLevelLineEdit->text().toStdString();
        logger.level = level_from_string(config["LOG_LEVEL"]);
        edited = true;
    }

    if (edited) {
        update_config_dictionary("config_file.conf", config);
        LOG_INFO(logger, "Configuration updated");
    } else {
        LOG_INFO(logger, "No changes made to configuration");
    }

    emit backRequested();
}