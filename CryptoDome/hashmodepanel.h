#ifndef HASHMODEPANEL_H
#define HASHMODEPANEL_H

#include <QWidget>
#include <QFileDialog>
#include <QMessageBox>
#include <QFileInfo>
#include <QFile>
#include <QDate>
#include <QTime>
#include <QTextStream>
#include "hashmanager.h"

namespace Ui {
class HashModePanel;
}

class HashModePanel : public QWidget
{
    Q_OBJECT

public:
    explicit HashModePanel(QWidget *parent = nullptr);
    ~HashModePanel();

private:
    Ui::HashModePanel *ui;

    void onClick_btnBrowseFile();
    void onClick_btnBrowseCompareFile();
    void onClick_btnGetHash();
    void showMsg(QString title, QString msg);
    void saveResult();
    void toggleCompare();
};

#endif // HASHMODEPANEL_H
