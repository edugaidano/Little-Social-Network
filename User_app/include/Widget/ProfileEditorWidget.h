#ifndef PROFILE_EDITOR_WIDGET_H
#define PROFILE_EDITOR_WIDGET_H

#include <QWidget>

#include "Widget/ProfileWidget.h"

#include "logs/logs.h" // on Global folder

QT_BEGIN_NAMESPACE
namespace Ui { class ProfileEditorWidget; }
QT_END_NAMESPACE

class ProfileEditorWidget : public QWidget
{
    Q_OBJECT

public:
    explicit ProfileEditorWidget(
        LOG_T &logger,
        const QString &username, 
        const QString &profileContent, 
        QWidget *parent = nullptr
    );
    ~ProfileEditorWidget();

signals:
    void backToMenuRequested();
    void saveProfileRequested(QString profileContent);

private slots:
    void onBackButtonClicked();
    void onSaveButtonClicked();

private:
    LOG_T &logger;
    Ui::ProfileEditorWidget *ui;
};

#endif // PROFILE_EDITOR_WIDGET_H