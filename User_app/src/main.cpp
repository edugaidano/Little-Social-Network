#include <QApplication>

#include "appController/app_controller.h"
// on utils folder
#include "logs/logs.h"
#include "config/config.h"

int main(int argc, char *argv[])
{
    CONFIG_D config = get_config_dictionary("User.conf");
    LOG_LEVEL log_level = level_from_string(config["LOG_LEVEL"]);
    LOG_T logger = log_init(log_level, "app.log");
    LOG_INFO(logger, "Application started");

    QApplication a(argc, argv);

    AppController app(logger, config);
    app.show();

    return a.exec();
}