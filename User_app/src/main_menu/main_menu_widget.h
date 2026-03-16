#ifndef MAIN_MENU_WIDGET_H
#define MAIN_MENU_WIDGET_H

#include <QWidget>

#include "logs/logs.h" // on utils folder

QT_BEGIN_NAMESPACE
namespace Ui { class MainMenuWidget; }
QT_END_NAMESPACE

class MainMenuWidget : public QWidget
{
    Q_OBJECT

public:
    explicit MainMenuWidget(LOG_T &logger, QWidget *parent = nullptr);
    ~MainMenuWidget();

signals:
    void viewProfileRequested();
    void searchProfileRequested();
    void viewMessagesRequested();
    void sendMessageRequested();
    void logoutRequested();    

private slots:
    void onViewProfileButtonClicked();
    void onSearchProfileButtonClicked();
    void onViewMessagesButtonClicked();
    void onSendMessageButtonClicked();
    void onLogoutButtonClicked();

private:
    LOG_T &logger;
    Ui::MainMenuWidget *ui;
};

#endif // MAIN_MENU_WIDGET_H