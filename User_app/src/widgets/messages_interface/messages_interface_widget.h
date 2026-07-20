#ifndef MESSAGES_INTERFACE_WIDGET_H
#define MESSAGES_INTERFACE_WIDGET_H

#include <QWidget>

#include "../message_item/message_item_widget.h"
#include "../../dialog/dialog.h"

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
    MessageItemWidget* findMessageById(uint32_t id);
    void removeMessage(uint32_t id);
    void checkMessagesToDisplay();

signals:
    void backToMainMenu();
    void messageSelected(uint32_t messageId);

private slots:
    void onBackButtonClicked();
    void onMessageItemClicked(const uint32_t messageId);

private:
    LOG_T &logger;
    std::unordered_map<uint32_t, MessageItemWidget*> messageMap;
    Ui::MessagesInterfaceWidget *ui;
};

#endif // MESSAGES_INTERFACE_WIDGET_H