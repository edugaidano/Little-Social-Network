#ifndef SEND_MESSAGE_WIDGET_H
#define SEND_MESSAGE_WIDGET_H

#include <QWidget>

#include "logs/logs.h" // on utils folder

QT_BEGIN_NAMESPACE
namespace Ui { class SendMessageWidget; }
QT_END_NAMESPACE

class SendMessageWidget : public QWidget
{
    Q_OBJECT

public:
    explicit SendMessageWidget(LOG_T &logger, QWidget *parent = nullptr);
    ~SendMessageWidget();

signals:
    void sendMessage(const QString &destinatary, const QString &subject, const QString &content);
    void cancelMessage();

private slots:
    void onSendButtonClicked();
    void onCancelButtonClicked();

private:
    LOG_T &logger;
    Ui::SendMessageWidget *ui;
};

#endif // SEND_MESSAGE_WIDGET_H