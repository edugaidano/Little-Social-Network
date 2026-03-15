#include <QApplication>

#include "appController/app_controller.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    AppController app;
    app.show();

    return a.exec();
}