#ifndef PASSWORDGENERATORDIALOG_H
#define PASSWORDGENERATORDIALOG_H

#include <QDialog>
#include <QDebug>
#include <QClipboard>
#include <QMessageBox>
#include <QShortcut>
#include "graphicgenerator.h"

namespace Ui {
class PasswordGeneratorDialog;
}

class PasswordGeneratorDialog : public QDialog
{
    Q_OBJECT

public:
    explicit PasswordGeneratorDialog(QWidget *parent = nullptr);
    ~PasswordGeneratorDialog();

private:
    Ui::PasswordGeneratorDialog *ui;
    GraphicGenerator *generator = nullptr;
    QShortcut *copyCloseShortcut;

private slots:
    void btnStartGen_onClick();
    void genEnd();
    void btnCopy_onClick();
    void copyClose();
};

#endif // PASSWORDGENERATORDIALOG_H
