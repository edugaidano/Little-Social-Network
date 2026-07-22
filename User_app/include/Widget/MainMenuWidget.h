#ifndef MAIN_MENU_WIDGET_H
#define MAIN_MENU_WIDGET_H

#include <QWidget>

#include "logs/logs.h" // on Global folder

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
    void viewInboxRequested();
    void sendMessageRequested();
    void logoutRequested();    

private slots:
    void onViewProfileButtonClicked();
    void onSearchProfileButtonClicked();
    void onViewInboxButtonClicked();
    void onSendMessageButtonClicked();
    void onLogoutButtonClicked();

    void changeEvent(QEvent *event);

private:
    LOG_T &logger;
    Ui::MainMenuWidget *ui;
};

#endif // MAIN_MENU_WIDGET_H