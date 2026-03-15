#ifndef MAIN_MENU_WIDGET_H
#define MAIN_MENU_WIDGET_H

#include <QWidget>

QT_BEGIN_NAMESPACE
namespace Ui { class MainMenuWidget; }
QT_END_NAMESPACE

class MainMenuWidget : public QWidget
{
    Q_OBJECT

public:
    explicit MainMenuWidget(QWidget *parent = nullptr);
    ~MainMenuWidget();

signals:
    void viewProfileRequested();
    void searchProfileRequested();
    void viewMessagesRequested();
    void sendMessageRequested();
    void logoutRequested();    

private:
    Ui::MainMenuWidget *ui;
};

#endif // MAIN_MENU_WIDGET_H