#ifndef SEARCH_WIDGET_H
#define SEARCH_WIDGET_H

#include <QWidget>

#include "dialog.h"

#include "logs/logs.h" // on utils folder

QT_BEGIN_NAMESPACE
namespace Ui { class SearchProfileWidget; }
QT_END_NAMESPACE

class SearchProfileWidget : public QWidget
{
    Q_OBJECT

public:
    explicit SearchProfileWidget(LOG_T &logger, QWidget *parent = nullptr);
    ~SearchProfileWidget();

signals:
    void searchProfile(QString username);
    void backToMainMenu();

private slots:
    void onSearchButtonClicked();
    void onBackButtonClicked();

private:
    LOG_T &logger;
    Ui::SearchProfileWidget *ui;
};

#endif // SEARCH_WIDGET_H