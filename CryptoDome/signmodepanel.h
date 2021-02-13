#ifndef SIGNMODEPANEL_H
#define SIGNMODEPANEL_H

#include <QWidget>
#include <QMessageBox>
#include <QFileDialog>
#include <signmanager.h>

namespace Ui {
class SignModePanel;
}

class SignModePanel : public QWidget
{
    Q_OBJECT

public:
    explicit SignModePanel(QWidget *parent = nullptr);
    ~SignModePanel();

private:
    Ui::SignModePanel *ui;

    void check_rbGenKey();
    void onClick_btnCreateSign();
    void onClick_btnVerifySign();
    void onClick_btnBrowseFilePath();
    void onClick_btnBrowseSignPath();
    void onClick_btnBrowsePubKeyPath();
    void onClick_btnBrowsePrKeyPath();
    void onCLick_btnBrowseKeyPath();
    void onClick_btnBrowseFilePathV();
    void onClick_btnBrowsePubKeyPathV();
    void onClick_btnBrowseSignPathV();
    void showMessage(QString title, QString text);
};

#endif // SIGNMODEPANEL_H
