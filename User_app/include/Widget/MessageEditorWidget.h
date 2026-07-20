#ifndef MESSAGE_EDITOR_WIDGET_H
#define MESSAGE_EDITOR_WIDGET_H

#include <QWidget>

#include "dialog.h"

#include "logs/logs.h" // on utils folder

QT_BEGIN_NAMESPACE
namespace Ui { class MessageEditorWidget; }
QT_END_NAMESPACE

class MessageEditorWidget : public QWidget
{
    Q_OBJECT

public:
    explicit MessageEditorWidget(LOG_T &logger, QWidget *parent = nullptr);
    ~MessageEditorWidget();

signals:
    void sendMessage(std::string destinatary, std::string subject, std::string content);
    void backRequested();

private slots:
    void onSendButtonClicked();
    void onBackButtonClicked();

private:
    LOG_T &logger;
    Ui::MessageEditorWidget *ui;
};

#endif // MESSAGE_EDITOR_WIDGET_H