#ifndef LOGIN_WIDGET_H
#define LOGIN_WIDGET_H

#include <QWidget>

#include "logs/logs.h" // on utils folder

QT_BEGIN_NAMESPACE
namespace Ui { class LoginWidget; }
QT_END_NAMESPACE

class LoginWidget : public QWidget
{
    Q_OBJECT

public:
    explicit LoginWidget(LOG_T &logger, QWidget *parent = nullptr);
    ~LoginWidget();

signals:
    void loginRequested(QString user);
    void registerRequested(QString user);
    void configRequested();

private slots:
    void onMainButtonClicked();
    void onSecondaryButtonClicked();
    void onConfigButtonClicked();

private:
    LOG_T &logger;
    bool isLoginMode = true; // true: login mode, false: register mode
    Ui::LoginWidget *ui;
};

#endif // LOGIN_WIDGET_H