#ifndef MESSAGES_INTERFACE_WIDGET_H
#define MESSAGES_INTERFACE_WIDGET_H

#include <QWidget>

#include "logs/logs.h" // on utils folder

QT_BEGIN_NAMESPACE
namespace Ui { class MessagesInterfaceWidget; }
QT_END_NAMESPACE

class MessagesInterfaceWidget : public QWidget
{
    Q_OBJECT

public:
    explicit MessagesInterfaceWidget(LOG_T &logger, QWidget *parent = nullptr);
    ~MessagesInterfaceWidget();
    void addMessageItem(const uint32_t messageId, bool seen, const QString &date, const QString &sender, const QString &subject);

signals:
    void backToMainMenu();
    void messageSelected(const uint32_t messageId);

private slots:
    void onBackButtonClicked();
    void onMessageItemClicked(const uint32_t messageId);

private:
    LOG_T &logger;
    Ui::MessagesInterfaceWidget *ui;
};

#endif // MESSAGES_INTERFACE_WIDGET_H