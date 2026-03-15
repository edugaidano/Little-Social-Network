#ifndef MESSAGE_WIDGET_H
#define MESSAGE_WIDGET_H

#include <QWidget>

QT_BEGIN_NAMESPACE
namespace Ui { class MessageWidget; }
QT_END_NAMESPACE

class MessageWidget : public QWidget
{
    Q_OBJECT

public:
    explicit MessageWidget(const uint32_t id, const QString &date ,const QString &sender, const QString &subject, const QString &content, QWidget *parent = nullptr);
    ~MessageWidget();

signals:
    void backButtonClicked();
    void deleteButtonClicked(const uint32_t id);

private:
    Ui::MessageWidget *ui;
    const uint32_t messageId;
};

#endif // MESSAGE_WIDGET_H