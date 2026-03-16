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

private slots:
    void onLoginButtonClicked();
    void onRegisterButtonClicked();

private:
    LOG_T &logger;
    Ui::LoginWidget *ui;
};

#endif // LOGIN_WIDGET_H