#ifndef INBOX_WIDGET_H
#define INBOX_WIDGET_H

#include <QWidget>

#include "MessageItemWidget.h"
#include "dialog.h"

#include "logs/logs.h" // on utils folder

QT_BEGIN_NAMESPACE
namespace Ui { class InboxWidget; }
QT_END_NAMESPACE

class InboxWidget : public QWidget
{
    Q_OBJECT

public:
    explicit InboxWidget(LOG_T &logger, QWidget *parent = nullptr);
    ~InboxWidget();
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
    Ui::InboxWidget *ui;
};

#endif // INBOX_WIDGET_H