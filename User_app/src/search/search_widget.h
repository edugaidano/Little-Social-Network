#ifndef SEARCH_WIDGET_H
#define SEARCH_WIDGET_H

#include <QWidget>

#include "logs/logs.h" // on utils folder

QT_BEGIN_NAMESPACE
namespace Ui { class SearchWidget; }
QT_END_NAMESPACE

class SearchWidget : public QWidget
{
    Q_OBJECT

public:
    explicit SearchWidget(LOG_T &logger, QWidget *parent = nullptr);
    ~SearchWidget();

signals:
    void searchProfile(const QString &username);
    void backToMainMenu();

private slots:
    void onSearchButtonClicked();
    void onBackButtonClicked();

private:
    LOG_T &logger;
    Ui::SearchWidget *ui;
};

#endif // SEARCH_WIDGET_H