#include "AppController/AppController.h"

int main(int argc, char *argv[]) {    
    QApplication a(argc, argv);
    
    AppController app(a);

    app.show();

    return a.exec();
}