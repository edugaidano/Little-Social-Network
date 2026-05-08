#ifndef PROFILE_WIDGET_H
#define PROFILE_WIDGET_H

#include <QWidget>

#include "logs/logs.h" // on utils folder

QT_BEGIN_NAMESPACE
namespace Ui { class ProfileWidget; }
QT_END_NAMESPACE

class ProfileWidget : public QWidget
{
    Q_OBJECT

public:
    explicit ProfileWidget(
        LOG_T &logger,
        const QString &username, 
        const QString &profileContent, 
        const QString &extraAction, 
        QWidget *parent = nullptr
    );
    ~ProfileWidget();
    const QString &username;
    const QString &profileContent;
    const QString &extraAction;
    
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