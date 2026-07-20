#ifndef APP_CONTROLLER_H
#define APP_CONTROLLER_H

#include <QApplication>
#include <QWidget>
#include <QTranslator>
#include <QStackedWidget>
#include <QLayout>
#include <QMessageBox>

#include "Communicator.h"
#include "dialog.h"

#include "config/config.h"
#include "logs/logs.h"


class AppController : public QWidget {
private:
    QApplication& app;
    QStackedWidget* stack;
    std::unique_ptr<Communicator> communicator;
    QTranslator translator;
    CONFIG_D config;
    LOG_T logger;

public:
    AppController(QApplication& application);
    ~AppController();

    void setLanguage();

    void startCommunicator();

    void addWidget(QWidget* w);
    void setCurrentWidget(QWidget* w);
    void removeWidget(QWidget* w);

    PACKAGE_T* doRequestToServer(PACKAGE_T* pkgRequest, CODE_CONTENT codeReply);

    CONFIG_D& getConfig() {return config;}
    void setConfig(CONFIG_D& newConfig);

    void setLogLevel(LOG_LEVEL level);
};

#endif