#ifndef PROFILE_WIDGET_H
#define PROFILE_WIDGET_H

#include <QWidget>

#include "logs/logs.h" // on Global folder

QT_BEGIN_NAMESPACE
namespace Ui { class ProfileWidget; }
QT_END_NAMESPACE

class ProfileWidget : public QWidget
{
    Q_OBJECT

public:
    explicit ProfileWidget(
        LOG_T &logger,
        QString username, 
        QString profileContent, 
        QString extraAction, 
        QWidget *parent = nullptr
    );
    ~ProfileWidget();
    void reloadContent(std::string content);
    QString username;
    QString profileContent;
    QString extraAction;
    
signals:
    void backToMenuRequested();
    void actionRequested();

private slots:
    void onBackButtonClicked();
    void onActionButtonClicked();

private:
    LOG_T &logger;
    Ui::ProfileWidget *ui;
};

#endif // PROFILE_WIDGET_H