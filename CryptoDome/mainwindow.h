#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QDebug>
#include "filemodepanel.h"
#include "textmodepanel.h"
#include "signmodepanel.h"
#include "hashmodepanel.h"
#include "idlepanel.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    FileModePanel *fileModePanel = nullptr;
    TextModePanel *textModePanel = nullptr;
    SignModePanel *signModePanel = nullptr;
    HashModePanel *hashModePanel = nullptr;
    idlePanel *idleModePanel = nullptr;

    bool panelIsOpened = false;
    bool fileModeIsOpened = false;
    bool textModeIsOpened = false;
    bool signModeIsOpened = false;
    bool hashModeIsOpened = false;

    void onClick_btnFileModePanel();
    void onClick_btnTextModePanel();
    void onClick_btnSignModePanel();
    void onClick_btnHashModePanel();
    void clearLayout();
};
#endif // MAINWINDOW_H
