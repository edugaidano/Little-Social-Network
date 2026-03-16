#include <QApplication>

#include "appController/app_controller.h"
#include "logs/logs.h" // on utils folder

int main(int argc, char *argv[])
{
    LOG_T logger = log_init(LEVEL_DEBUG, "app.log");
    LOG_DEBUG(logger, "Application started");
    //TODO: add option to change log level and file name from a config file

    QApplication a(argc, argv);

    AppController app(logger);
    app.show();

    return a.exec();
}