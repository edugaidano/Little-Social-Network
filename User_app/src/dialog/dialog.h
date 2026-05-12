#ifndef DIALOG_H
#define DIALOG_H

#include <QMessageBox>

#define DIALOG_INFO(parentWidget, text) QMessageBox::information(parentWidget, "INFO", text)
#define DIALOG_WARNING(parentWidget, text) QMessageBox::warning(parentWidget, "WARNING", text)
#define DIALOG_ERROR(parentWidget, text) QMessageBox::critical(parentWidget, "ERROR", text)

#endif // DIALOG_H