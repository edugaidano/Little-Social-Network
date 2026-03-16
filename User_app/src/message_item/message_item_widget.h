#ifndef MESSAGE_ITEM_WIDGET_H
#define MESSAGE_ITEM_WIDGET_H

#include <QWidget>

#include "logs/logs.h" // on utils folder

QT_BEGIN_NAMESPACE
namespace Ui { class MessageItemWidget; }
QT_END_NAMESPACE

class MessageItemWidget : public QWidget
{
    Q_OBJECT

public:
    const uint32_t messageId;
    explicit MessageItemWidget(
        LOG_T &logger,
        bool seen, 
        const uint32_t messageId, 
        const QString &date, 
        const QString &sender, 
        const QString &subject, 
        QWidget *parent = nullptr
    );
    ~MessageItemWidget();
    void mousePressEvent(QMouseEvent *event) override;

signals:
    void clicked(const uint32_t messageId);

private:
    LOG_T &logger;
    Ui::MessageItemWidget *ui;
};

#endif // MESSAGE_ITEM_WIDGET_H