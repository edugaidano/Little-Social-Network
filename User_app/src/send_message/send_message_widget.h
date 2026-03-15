#ifndef SEND_MESSAGE_WIDGET_H
#define SEND_MESSAGE_WIDGET_H

#include <QWidget>

QT_BEGIN_NAMESPACE
namespace Ui { class SendMessageWidget; }
QT_END_NAMESPACE

class SendMessageWidget : public QWidget
{
    Q_OBJECT

public:
    explicit SendMessageWidget(QWidget *parent = nullptr);
    ~SendMessageWidget();

signals:
    void sendMessage(const QString &destinatary, const QString &subject, const QString &content);
    void cancelMessage();

private:
    Ui::SendMessageWidget *ui;
};

#endif // SEND_MESSAGE_WIDGET_H