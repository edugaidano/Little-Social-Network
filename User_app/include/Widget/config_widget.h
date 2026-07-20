#ifndef CONFIG_WIDGET_H
#define CONFIG_WIDGET_H

#include <QWidget>

// on utils folder
#include "logs/logs.h" 
#include "config/config.h"

QT_BEGIN_NAMESPACE
namespace Ui { class ConfigWidget; }
QT_END_NAMESPACE

class ConfigWidget : public QWidget
{
    Q_OBJECT

public:
    explicit ConfigWidget(LOG_T &logger, CONFIG_D &config, QWidget *parent = nullptr);
    ~ConfigWidget();    

signals:
    void backRequested();
    void saveRequested(CONFIG_D config);

private slots:
    void onSaveButtonClicked();
    void onCancelButtonClicked();

private:
    LOG_T &logger;
    Ui::ConfigWidget *ui;
};

#endif // CONFIG_WIDGET_H