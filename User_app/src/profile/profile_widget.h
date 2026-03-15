#ifndef PROFILE_WIDGET_H
#define PROFILE_WIDGET_H

#include <QWidget>

QT_BEGIN_NAMESPACE
namespace Ui { class ProfileWidget; }
QT_END_NAMESPACE

class ProfileWidget : public QWidget
{
    Q_OBJECT

public:
    explicit ProfileWidget(const QString &username, const QString &profileContent, const QString &extraAction, QWidget *parent = nullptr);
    ~ProfileWidget();
    
signals:
    void backToMenuRequested();
    void actionRequested();

private:
    Ui::ProfileWidget *ui;
};

#endif // PROFILE_WIDGET_H