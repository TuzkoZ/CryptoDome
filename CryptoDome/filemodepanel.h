#ifndef FILEMODEPANEL_H
#define FILEMODEPANEL_H

#include <QWidget>
#include <QFileInfo>
#include <QFileDialog>
#include <QMessageBox>
#include <QFileInfo>
#include "cryptmanager.h"

namespace Ui {
class FileModePanel;
}

class FileModePanel : public QWidget
{
    Q_OBJECT

public:
    explicit FileModePanel(QWidget *parent = nullptr);
    ~FileModePanel();

private:
    Ui::FileModePanel *ui;
    void onClick_btnBrowseFile();
    void onClick_btnBrowseFile_D();
    void onClick_btnEncryptFile();
    void onClick_btnDecryptFile();
    void showMsg(QString title, QString text);
    bool checkFile(QString filePath);
};

#endif // FILEMODEPANEL_H
