#ifndef MESSAGE_WIDGET_H
#define MESSAGE_WIDGET_H

#include <QWidget>

#include "logs/logs.h" // on Global folder

QT_BEGIN_NAMESPACE
namespace Ui { class MessageWidget; }
QT_END_NAMESPACE

class MessageWidget : public QWidget
{
    Q_OBJECT

public:
    explicit MessageWidget(
        LOG_T &logger,
        uint32_t id, 
        QString date,
        QString sender,
        QString subject, 
        QString content, 
        QWidget *parent = nullptr
    );
    ~MessageWidget();

signals:
    void backButtonClicked();
    void deleteButtonClicked(uint32_t id);

private slots:
    void onBackButtonClicked();
    void onDeleteButtonClicked();

private:
    LOG_T &logger;
    Ui::MessageWidget *ui;
    uint32_t messageId;
};

#endif // MESSAGE_WIDGET_H