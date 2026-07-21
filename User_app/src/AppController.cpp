#include "AppController.h"
#include "WidgetController/LoginController.h"

AppController::AppController(QApplication& application) :
    app(application)
{
    config = get_config_dictionary("User.conf");
    LOG_LEVEL log_level = level_from_string(config["LOG_LEVEL"]);
    logger = log_init(log_level, "app.log");

    stack = new QStackedWidget();

    QVBoxLayout *layout = new QVBoxLayout(this);
    layout->addWidget(stack);

    setLanguage();

    new LoginController(logger, *this);

    LOG_INFO(logger, "Application started");
}

AppController::~AppController() {
}

void AppController::setLanguage() {
    app.removeTranslator(&translator);

    if (translator.load(("app_" + config["LANGUAGE"]).c_str())) {
        app.installTranslator(&translator);
    }
}

void AppController::startCommunicator() {
    communicator = std::make_unique<Communicator>(
        logger, 
        config["SERVER_IP"].c_str(), 
        config["SERVER_PORT"].c_str()
    );
}

void AppController::addWidget(QWidget* w) {
    stack->addWidget(w);
}

void AppController::setCurrentWidget(QWidget* w) {
    if (stack->indexOf(w) == -1)
        addWidget(w);
    stack->setCurrentWidget(w);
}

void AppController::removeWidget(QWidget* w) {
    stack->removeWidget(w);
}

void AppController::setConfig(CONFIG_D& newConfig) {
    for (const auto& [key, value] : newConfig) {
        config[key] = value;
    }

    update_config_dictionary("config_file.conf", config);
}

void AppController::setLogLevel(LOG_LEVEL level) {
    logger.level = level;
}