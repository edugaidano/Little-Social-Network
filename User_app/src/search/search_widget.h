#ifndef SEARCH_WIDGET_H
#define SEARCH_WIDGET_H

#include <QWidget>

QT_BEGIN_NAMESPACE
namespace Ui { class SearchWidget; }
QT_END_NAMESPACE

class SearchWidget : public QWidget
{
    Q_OBJECT

public:
    explicit SearchWidget(QWidget *parent = nullptr);
    ~SearchWidget();

signals:
    void searchProfile(const QString &username);
    void backToMainMenu();

private slots:
    void on_searchButton_clicked();

private:
    Ui::SearchWidget *ui;
};

#endif // SEARCH_WIDGET_H